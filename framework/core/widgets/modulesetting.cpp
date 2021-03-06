﻿#include "modulesetting.h"

#include <QTreeView>
#include <QHBoxLayout>
#include <QAction>
#include <QHeaderView>
#include <QEvent>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QQuickWidget>

#include <base/util/rsingleton.h>
#include <base/actionmanager/actionmanager.h>
#include <base/actionmanager/action.h>
#include <base/util/rutil.h>
#include <base/util/widgetanimation.h>
#include <core/pluginmanager/plugin/pluginmanager.h>
#include <core/pluginmanager/plugin/pluginloader.h>
#include <core/pluginmanager/interface/rcomponent.h>
#include <core/network/taskmanager.h>
#include "setting/systemsetting.h"
#include "../selfwidget/mytabwidget.h"

namespace Core{

class QmlModuleDetailDialog;

MSettingModel::MSettingModel(QTreeView *view, QObject *parent):treeView(view),QAbstractItemModel(parent)
{
    rootNode = new TreeNode;

    //按照插件所属的类别归纳显示
    Core::PluginManager::ActiveComponentMap maps = Core::PluginManager::instance()->getAllActivePlugins();
    Core::PluginManager::ActiveComponentMap::iterator iter = maps.begin();
    while(iter != maps.end()){
        Core::RComponent * comp = iter.value().pComp;
        QStringList slist = comp->id().toString().split(".");
        QString menuId = slist.at(0)+"."+slist.at(1);

        TreeNode * existedNode = NULL;
        auto findex = std::find_if(rootNode->nodes.begin(),rootNode->nodes.end(),[&](TreeNode * node){
            return node->nodeId == menuId;
        });

        if(findex == rootNode->nodes.end()){
            existedNode = new TreeNode;
            existedNode->index = rootNode->nodes.size();
            existedNode->nodeId = menuId;
            existedNode->nodeName = comp->pluginName();
            existedNode->parentNode = NULL;
            rootNode->nodes.push_back(existedNode);
        }else{
            existedNode = *findex;
        }

        TreeNode * childNode = new TreeNode;
        childNode->nodeId = comp->id().toString();
        childNode->nodeName = comp->getDockContainer()->toggleViewAction()->text();
        childNode->objName = comp->getDockContainer()->objectName();
        childNode->parentNode = existedNode;
        childNode->index = existedNode->nodes.size();
        childNode->visible = true;
        nodeMap.insert(childNode->nodeId,childNode);
        existedNode->nodes.push_back(childNode);
        QObject::connect(comp->getDockContainer()->toggleViewAction(),SIGNAL(triggered(bool)),this,SLOT(userTriggered(bool)));
        QObject::connect(comp->getDockContainer()->toggleViewAction(),SIGNAL(toggled(bool)),this,SLOT(userTriggered(bool)));
        iter++;
    }
    headList<<(QObject::tr("Plugin Name"));
}

MSettingModel::~MSettingModel()
{

}

QVariant MSettingModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    TreeNode *item = static_cast<TreeNode*>(index.internalPointer());
    if(item == NULL)
        return QVariant();

    switch(role){
        case Qt::DisplayRole:
            return item->nodeName;
            break;
        case Qt::CheckStateRole:
            //不能直接返回item->visible，而需要返回CheckState的枚举值
            if(item->parentNode){
                return item->visible ? Qt::Checked : Qt::Unchecked;
            }else{
                int visibleItemSize = std::count_if(item->nodes.begin(),item->nodes.end(),[&](TreeNode * item){
                                return item->visible;
                           });
                if(visibleItemSize == 0){
                    return Qt::Unchecked;
                }else if(visibleItemSize == item->nodes.size()){
                    return Qt::Checked;
                }else{
                    return Qt::PartiallyChecked;
                }
            }
            break;
        default:
            break;
    }
    return QVariant();
}

Qt::ItemFlags MSettingModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    if(index.column() == 0)
         return flags | Qt::ItemIsUserCheckable;

    return flags;
}

QVariant MSettingModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && section == 0){
        switch (role){
            case  Qt::DisplayRole:
                return headList.at(section);
                break;
            case  Qt::BackgroundColorRole:
                return QColor(0,255,0,50);
                break;
            default:
                break;
        }
    }
    return QVariant();
}

QModelIndex MSettingModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeNode * parentItem;

    if (!parent.isValid())
        parentItem = rootNode;
    else
        parentItem = static_cast<TreeNode*>(parent.internalPointer());

    TreeNode * childItem = parentItem->nodes.at(row);

    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex MSettingModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeNode *childItem = static_cast<TreeNode*>(index.internalPointer());
    TreeNode *parentItem = childItem->parentNode;

    if (parentItem == rootNode || parentItem == NULL)
        return QModelIndex();

    return createIndex(parentItem->index, 0, parentItem);
}

int MSettingModel::rowCount(const QModelIndex &parent) const
{
    TreeNode *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootNode;
    else
        parentItem = static_cast<TreeNode*>(parent.internalPointer());

    return parentItem->nodes.size();
}

int MSettingModel::columnCount(const QModelIndex &) const
{
    return 1;
}

bool MSettingModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    TreeNode * node = static_cast<TreeNode *>(index.internalPointer());
    if(node == NULL)
        return false;

    QVector<int> roles;
    switch(role){
        case Qt::CheckStateRole:
            if(node->parentNode){
                node->visible = (value == Qt::Checked);
            }else{
                std::for_each(node->nodes.begin(),node->nodes.end(),[&](TreeNode * item){
                    item->visible = (value == Qt::Checked);
                });
            }
            emit moduleStateChanged(node);
            roles.push_back(Qt::CheckStateRole);
            break;
        default:
            break;
    }
    if(roles.size() > 0)
        emit dataChanged(index,index,roles);

    return true;
}

/*!
 * @brief 根据父、子节点，获取子节点的id
 * @param[in] parentIndex 父节点
 * @param[in] childIndex 子节点
 * @return 若存在则返回节点号，否则返回空
 */
QString MSettingModel::getNodeId(int parentIndex, int childIndex)
{
    if(parentIndex < 0 || parentIndex >= rootNode->nodes.size())
        return QString("");

    TreeNode * parentNode = rootNode->nodes.at(parentIndex);
    if(childIndex < 0 || childIndex >= parentNode->nodes.size())
        return QString("");

    return parentNode->nodes.at(childIndex)->nodeId;
}

/*!
 * @brief 响应菜单列表中action勾选
 * @param[in] triggered 是否选中
 */
void MSettingModel::userTriggered(bool triggered)
{
    QString objName = QObject::sender()->objectName();
    if(nodeMap.contains(objName)){
        nodeMap.value(objName)->visible = triggered;
        udpateModel();
    }
}

void MSettingModel::udpateModel()
{
    beginResetModel();
    endResetModel();
    treeView->expandAll();
}

class ModuleSettingPrivate
{
    Q_DECLARE_PUBLIC(ModuleSetting)
public:
    ModuleSettingPrivate(ModuleSetting * q):q_ptr(q),barVisible(true),rightContextMenu(NULL){
        contentMargins = QMargins(18,2,2,2);
        init();
    }

    void init();
    void initRightMenuAndAction();
    void retranslateUi();

    QWidget * mainWidget;
    ModuleSetting* q_ptr;

    QTreeView * treeView;
    MSettingModel * treeModel;

    QMargins contentMargins;        /*!< 主窗口内容边距 */
    QRect controlRect;              /*!< 控制显示/隐藏区域 */
    bool barVisible;                /*!< 控制面板是否显示 */
    Base::WidgetAnimation widgetAnimation;

    QMenu * rightContextMenu;       /*!< 右键菜单 */
};

void ModuleSettingPrivate::init()
{
    mainWidget = new QWidget(q_ptr);
//    mainWidget->setObjectName("mainWidget");

    treeView = new QTreeView(mainWidget);
    treeView->setContextMenuPolicy(Qt::CustomContextMenu);

    treeModel = new MSettingModel(treeView);
    QObject::connect(treeModel,SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),q_ptr,SLOT(updatePluginState(QModelIndex,QModelIndex,QVector<int>)));
    QObject::connect(treeModel,SIGNAL(moduleStateChanged(MSettingModel::TreeNode *)),q_ptr,SLOT(updateModuelState(MSettingModel::TreeNode *)));
    QObject::connect(treeView,SIGNAL(clicked(QModelIndex)),q_ptr,SLOT(raiseModule(QModelIndex)));
    QObject::connect(treeView,SIGNAL(customContextMenuRequested(QPoint)),q_ptr,SLOT(contextMenu(QPoint)));

    treeView->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);
    treeView->setFocusPolicy(Qt::NoFocus);
    treeView->header()->hide();
    treeView->setModel(treeModel);
    treeView->expandAll();

    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(contentMargins);
    mainLayout->addWidget(treeView);

    mainWidget->setLayout(mainLayout);

    QHBoxLayout * layout = new QHBoxLayout;
    layout->setContentsMargins(1,1,1,1);
    layout->addWidget(mainWidget);
    q_ptr->setLayout(layout);
    mainWidget->installEventFilter(q_ptr);
}

void ModuleSettingPrivate::initRightMenuAndAction()
{
    if(rightContextMenu == NULL){
        rightContextMenu = new QMenu();

        QAction * viewModuleDetail = new QAction();
        viewModuleDetail->setText(QObject::tr("More info"));
        QObject::connect(viewModuleDetail,SIGNAL(triggered(bool)),q_ptr,SLOT(viewModuleDetailInfo(bool)));

        rightContextMenu->addAction(viewModuleDetail);
    }
}

void ModuleSettingPrivate::retranslateUi()
{

}

ModuleSetting::ModuleSetting(QWidget *parent):Widget(parent),d_ptr(new ModuleSettingPrivate(this))
{
    setObjectName("dataview_modulesetting");
    Core::Subject::instance()->attach(this);
    setWidgetFeatures(getWidgetFeatures() & (~Widget::WidgetResizeable));
}

ModuleSetting::~ModuleSetting()
{

}

QSize ModuleSetting::sizeHint() const
{
    return QSize(310,450);
}

void ModuleSetting::onMessage(QString messageType)
{
    Q_D(ModuleSetting);
    if(messageType == QString(MessageType::MESS_LAN_CHANGED)){
        d->retranslateUi();
    }
}

bool ModuleSetting::eventFilter(QObject *watched, QEvent *event)
{
    Q_D(ModuleSetting);
    if(watched == d->mainWidget){
        switch(event->type()){
            case QEvent::Paint:
                {
                    QPainter painter(d->mainWidget);
                    QPainterPath ppath;
                    painter.setRenderHint(QPainter::Antialiasing,true);
                    QSize windowSize = d->mainWidget->size();
                    //边框
                    ppath.moveTo(windowSize.width(),0);
                    ppath.lineTo(d->contentMargins.left() * 2,0);
                    ppath.lineTo(d->contentMargins.left(),d->contentMargins.left());
                    ppath.lineTo(d->contentMargins.left(),(windowSize.height() - d->controlRect.height())/2);

                    ppath.lineTo(0,(windowSize.height() - d->controlRect.height())/2 + 10);
                    ppath.lineTo(0,windowSize.height() / 2 + d->controlRect.height()/2 - 10);

                    ppath.lineTo(d->contentMargins.left(),windowSize.height() / 2 + d->controlRect.height()/2);
                    ppath.lineTo(d->contentMargins.left(),windowSize.height() - d->contentMargins.left());
                    ppath.lineTo(d->contentMargins.left() * 2,windowSize.height());
                    ppath.lineTo(windowSize.width(),windowSize.height());
                    ppath.moveTo(windowSize.width(),0);

                    //线条
                    QPainterPath linePath;
                    linePath.moveTo(d->contentMargins.left(),windowSize.height() / 3 * 2 + d->controlRect.height());
                    linePath.lineTo(d->contentMargins.left(),windowSize.height() - d->contentMargins.left());
                    linePath.lineTo(d->contentMargins.left() * 2,windowSize.height());
                    linePath.lineTo(d->contentMargins.left() * 2 + 50,windowSize.height());
                    linePath.lineTo(d->contentMargins.left() * 2 + 42,windowSize.height() - 6);
                    linePath.lineTo(d->contentMargins.left() * 2 - d->contentMargins.left() / 2,windowSize.height() - 6);
                    linePath.lineTo(d->contentMargins.left() + 6,windowSize.height() - d->contentMargins.left() - 10);
                    linePath.lineTo(d->contentMargins.left() + 6,windowSize.height() / 3 * 2 + d->controlRect.height() + 10);
                    linePath.lineTo(d->contentMargins.left(),windowSize.height() / 3 * 2 + d->controlRect.height());

                    QColor yellowColor(255,195,0,245);

                    painter.save();
                    painter.setPen(Qt::NoPen);
                    painter.fillPath(ppath,QBrush(QColor(13,26,42,150)));
                    painter.fillPath(linePath,QBrush(yellowColor));
                    painter.setPen(QColor(0,204,255,150));
                    painter.drawPath(ppath);
                    painter.restore();

                    painter.save();
                    QPoint cpoint = d->controlRect.center();
                    int radius = 5;
                    painter.setPen(Qt::NoPen);
                    painter.setBrush(yellowColor);
                    QSize rectSize(2 * radius,2);
                    if(d->barVisible){
                        painter.drawRect(QRect(cpoint.x()- radius,cpoint.y() - rectSize.height() / 2,rectSize.width(),rectSize.height()));
                    }else{
                        painter.drawRect(QRect(cpoint.x()- radius,cpoint.y() - rectSize.height()/2,rectSize.width(),rectSize.height()));
                        painter.drawRect(QRect(cpoint.x()-rectSize.height()/2,cpoint.y() - radius,rectSize.height(),rectSize.width()));
                    }
                    painter.restore();
                }
                break;
            case QEvent::Resize:
                {
                    QSize windowSize = d->mainWidget->size();
                    int height = 100;
                    d->controlRect.setTopLeft(QPoint(0,(windowSize.height() - height)/2));
                    d->controlRect.setBottomRight(QPoint(d->contentMargins.left(),(windowSize.height() + height)/2));
                }
                break;
            case QEvent::MouseButtonPress:
                {
                    QMouseEvent * eve = dynamic_cast<QMouseEvent *>(event);
                    if(eve && d->controlRect.contains(eve->pos())){
                        animationView(d->barVisible);
                        d->barVisible = !d->barVisible;
                    }
                    raise();
                }
                break;
            default:
                break;
        }
    }
    return Widget::eventFilter(watched,event);
}

void ModuleSetting::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    this->raise();
}

/*!
 * @brief 根据ModuleSetting具有的feature特点，对控件进行设置
 * @details 1.对控件扩展/收缩状态显示进行设置 @n
 */
void ModuleSetting::updateFeatures()
{
    Q_D(ModuleSetting);
    if(d->barVisible != testFeatures(WidgetExpanable)){
        animationView(d->barVisible);
        d->barVisible = !d->barVisible;
    }
}

/*!
 * @brief 树形节点中复选框值改变
 * @param[in]
 * @return
 */
void ModuleSetting::updatePluginState(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int> ())
{
    //    qDebug()<<topLeft.row()<<topLeft.column()<<bottomRight.row()<<bottomRight.column();
}

/*!
 * @brief 更新对应节点插件状态
 * @details 1.若dock未嵌入，直接控制显示隐藏；
            2.若dock嵌入，隐藏时，从tab中移除(依然tabbed).若只剩两个再隐藏其中一个时，将tab移除；
                显示时，若dock为1，tab不显示，再拖动嵌入时，产生新tab。
 * @param[in] node 发生数据更改的节点
 */
void ModuleSetting::updateModuelState(MSettingModel::TreeNode * node)
{
    Q_D(ModuleSetting);
    std::function<void(MSettingModel::TreeNode * node)> func =[&](MSettingModel::TreeNode * node){
        if(node->objName.isEmpty())
            return;
        RComponent * comp = PluginManager::instance()->getActivePlugin(node->objName);
        if(comp){
#ifndef OFFICAL_DOCK
            Datastruct::TabInfo tabInfo = comp->getDockContainer()->getTabInfo();
            if(tabInfo.tabbed){
                PluginManager::instance()->ungroupDockWidget(tabInfo.tabObjName,node->objName,QPoint(0,0));
            }
#endif
			Base::Action * selectedAction = Base::ActionManager::instance()->action(node->nodeId.toLocal8Bit().data());
            selectedAction->action()->setChecked(node->visible);
        }
    };
    if(node->parentNode){
        func(node);
    }else{
        std::for_each(node->nodes.begin(),node->nodes.end(),func);
    }
    d->treeView->update();
}

/*!
 * @brief 提升对应点击节点图层
 * @param[in] index 节点信息
 */
void ModuleSetting::raiseModule(QModelIndex index)
{
    Q_D(ModuleSetting);
    QModelIndex parent = index.parent();
    if(parent.isValid()){
       QString nodeId = d->treeModel->getNodeId(parent.row(),index.row());
       if(nodeId.isEmpty())
           return;
       emit raiseWidget(nodeId);
    }
}

/*!
 * @brief 自定义树形控件右键菜单
 * @attention 只有在非根节点上才可以显示右键菜单
 * @param[in]   point   右键事件触发点
 */
void ModuleSetting::contextMenu(QPoint point)
{
    Q_D(ModuleSetting);
    QModelIndex index = d->treeView->indexAt(point);
    if(index.isValid() && index.parent().isValid()){
        d->initRightMenuAndAction();
        d->rightContextMenu->exec(QCursor::pos());
    }
}

/*!
 * @brief 查看模块的详细信息
 * @details 查看插件协议信息、网络配置信息、插件信息等
 */
void ModuleSetting::viewModuleDetailInfo(bool checked)
{
    Q_UNUSED(checked)
    Q_D(ModuleSetting);

    QPoint treePoint = d->treeView->mapFromGlobal(d->rightContextMenu->pos());
    QModelIndex index = d->treeView->indexAt(treePoint);
    if(index.isValid()){
        MSettingModel::TreeNode * treeNode = static_cast<MSettingModel::TreeNode*>(index.internalPointer());
        if(treeNode){
            bool existed = false;
            Datastruct::ModuleInfo info = PluginManager::instance()->getActivePluginModuleInfo(treeNode->nodeId,existed);
            if(existed){
                //TODO 20181130将模块的详细信息以QML形式显示
                QmlModuleDetailDialog dialog(parentWidget());
                dialog.exec();
            }
        }
    }
}

void ModuleSetting::animationView(bool isVisible)
{
    Q_D(ModuleSetting);
    QRect screen = Base::RUtil::screenGeometry();
    if(isVisible){
        d->widgetAnimation.addAnimation(this,QRect(QPoint(screen.width() - d->controlRect.width(),y()),size()));
        currentFeatures &= ~Widget::WidgetExpanable;
    }else{
        d->widgetAnimation.addAnimation(this,QRect(QPoint(screen.width() - width(),y()),size()));
        currentFeatures |= Widget::WidgetExpanable;
    }
}


/************QML ****************/
class QmlModuleDetailDialogPrivate
{
    Q_DECLARE_PUBLIC(QmlModuleDetailDialog)
public:
    QmlModuleDetailDialogPrivate(QmlModuleDetailDialog * q):q_ptr(q){
        init();
    }

    void init();

    QmlModuleDetailDialog * q_ptr;
};

void QmlModuleDetailDialogPrivate::init()
{
    QQuickWidget * quickWidget = new QQuickWidget;

    QUrl source("qrc:/qml/QML/ModuleDetail.qml");
    quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView );
    quickWidget->setSource(source);

    q_ptr->setContentWidget(quickWidget);
}

QmlModuleDetailDialog::QmlModuleDetailDialog(QWidget *parent):Base::DialogProxy(parent),d_ptr(new QmlModuleDetailDialogPrivate(this))
{
    setTitle(tr("Module detail"));
}

QmlModuleDetailDialog::~QmlModuleDetailDialog()
{

}

QSize QmlModuleDetailDialog::sizeHint() const
{
    QRect screenSize = Base::RUtil::screenGeometry();
    return QSize(screenSize.width() * 0.23,screenSize.height() * 0.53);
}

}
