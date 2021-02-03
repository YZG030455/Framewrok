#include "targetdatabasemanagepage.h"

#include <QDebug>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QListView>

#include "../../utils/util.h"
#include "../../customwidget/customwidgetcontainer.h"

namespace Related {

	TargetDatabaseManagePage::TargetDatabaseManagePage(QWidget *parent)
		: AbstractPage(parent)
	{
		init();
		initConnect();
	}

	TargetDatabaseManagePage::~TargetDatabaseManagePage()
	{
	}

	PageType TargetDatabaseManagePage::getPageType() const
	{
		return Page_TargetDatabase_TargetOverview;
	}

	void TargetDatabaseManagePage::respToolButtPressed(OperationToolsPage::ButtType type)
	{
		switch (type)
		{
			case OperationToolsPage::Butt_Add: {

			}
											   break;
			case OperationToolsPage::Butt_Delete: {

			}
												  break;
			case OperationToolsPage::Butt_Edit: {

			}
												break;
			case OperationToolsPage::Butt_Refresh: {

			}
												   break;
			default:
				break;
		}
	}

	void TargetDatabaseManagePage::setPageNum(int page)
	{
	}

	void TargetDatabaseManagePage::setFixedPageRowCount(int pageItemCount)
	{
		m_tableModel->setFixedPageRowCount(pageItemCount);
	}

	void TargetDatabaseManagePage::init()
	{
		CustomWidgetContainer * cwidget = new CustomWidgetContainer();
		{
			m_operationToolsPage = new OperationToolsPage();
			connect(m_operationToolsPage, SIGNAL(buttPressed(OperationToolsPage::ButtType)),
				this, SLOT(respToolButtPressed(OperationToolsPage::ButtType)));

			//��ʱ���Դ���
			QWidget * conditionFilterWidget = new QWidget();
			QHBoxLayout * filterLayout = new QHBoxLayout();
			filterLayout->setContentsMargins(0, 0, 4, 0);
			conditionFilterWidget->setLayout(filterLayout);

			auto createLabel = [](QString text) {
				QLabel * label = new QLabel();
				label->setText(text);
				return label;
			};

			filterLayout->addWidget(createLabel(QStringLiteral("Ŀ������")));

			QComboBox * ct = new QComboBox();
			ct->setView(new QListView());
			QStringList ctList;
			ctList << QStringLiteral("ȫ������") << QStringLiteral("����") << QStringLiteral("����") << QStringLiteral("����");
			ct->addItems(ctList);

			filterLayout->addWidget(ct);
			filterLayout->addWidget(createLabel(QStringLiteral("����")));

			QComboBox * category = new QComboBox();
			category->setView(new QListView());
			QStringList cateList;
			cateList << QStringLiteral("ȫ������") << QStringLiteral("ˮ�潢") << QStringLiteral("�̴�") << QStringLiteral("�洬");
			category->addItems(cateList);
			
			filterLayout->addWidget(category);
			filterLayout->addWidget(createLabel(QStringLiteral("�ͺ�")));

			QComboBox * type = new QComboBox();
			type->setView(new QListView());
			QStringList tList;
			tList << QStringLiteral("ȫ���ͺ�") << QStringLiteral("XX��") << QStringLiteral("XXA��");
			type->addItems(tList);

			filterLayout->addWidget(type);

			QWidget * tmpWidget = new QWidget();
			QHBoxLayout * tmpLayout = new QHBoxLayout();
			tmpLayout->setContentsMargins(0, 0, 0, 0);
			tmpLayout->addWidget(m_operationToolsPage);
			tmpLayout->addStretch(1);
			tmpLayout->addWidget(conditionFilterWidget);
			tmpWidget->setLayout(tmpLayout);
			cwidget->setContent(tmpWidget);
		}

		CustomWidgetContainer * ctableView = new CustomWidgetContainer();
		{
			m_tableView = new Base::RTableView();
			m_tableView->setFocusPolicy(Qt::NoFocus);
			m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
			m_tableView->setSelectionMode(QAbstractItemView::SingleSelection);

			m_tableModel = new TargetDatabaseManageModel();
			m_tableModel->prepareData();

			m_tableView->setModel(m_tableModel);

			m_tableView->addColumnItem(Base::ColumnItem(T_Index, QStringLiteral("����")));
			m_tableView->addColumnItem(Base::ColumnItem(T_TargetName, QStringLiteral("Ŀ������"), 140));
			m_tableView->addColumnItem(Base::ColumnItem(T_Edttime, QStringLiteral("¼��ʱ��"), 180));
			m_tableView->addColumnItem(Base::ColumnItem(T_Tonnage, QStringLiteral("��λ(t)"), 180));
			m_tableView->addColumnItem(Base::ColumnItem(T_Lon, QStringLiteral("����"), 180));
			m_tableView->addColumnItem(Base::ColumnItem(T_Lat, QStringLiteral("γ��"), 180));
			m_tableView->addColumnItem(Base::ColumnItem(T_Speed, QStringLiteral("�����ٶ�"), 180));
			m_tableView->addColumnItem(Base::ColumnItem(T_AxlesNumber, QStringLiteral("����")));
			m_tableView->addColumnItem(Base::ColumnItem(T_Type, QStringLiteral("����")));

			m_pageSwitch = new PageSwitchBar();
			m_pageSwitch->setDataSize(m_tableModel->datasSize());
			connect(m_pageSwitch, SIGNAL(perPageNumsChanged(int)), this, SLOT(setFixedPageRowCount(int)));
			connect(m_pageSwitch, SIGNAL(switchPage(int)), this, SLOT(setPageNum(int)));

			QWidget * twidget = new QWidget();
			QVBoxLayout * cvlayout = new QVBoxLayout();
			cvlayout->setContentsMargins(0, 0, 0, 0);
			cvlayout->addWidget(m_tableView);
			cvlayout->addWidget(m_pageSwitch);
			twidget->setLayout(cvlayout);

			ctableView->setContent(twidget);
		}

		QVBoxLayout * vlayout = new QVBoxLayout();
		vlayout->setContentsMargins(4, 4, 4, 4);
		vlayout->addWidget(cwidget);
		vlayout->addWidget(ctableView);
		setLayout(vlayout);
	}

	void TargetDatabaseManagePage::initConnect()
	{

	}

}//namespace Related 
