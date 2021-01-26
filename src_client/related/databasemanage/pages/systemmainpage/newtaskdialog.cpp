#include "newtaskdialog.h"

#include <QDebug>

#include <base\util\rutil.h>
#include <base\selfwidget\rmessagebox.h>

#include "customwidget/customwidgetcontainer.h"
#include "../net/netconnector.h"
#include "../net/signaldispatch.h"
#include "../utils/util.h"
#include "../global.h"

namespace Related {

	NewTaskDialog::NewTaskDialog(QWidget *parent)
		: Base::DialogProxy(parent),
		m_newTaskInfoSetWidget(nullptr), 
		m_treeView(nullptr), 
		m_treeModel(nullptr),
		m_fileRootNode(nullptr)
	{
		init();
		this->setMinimumSize(800, 600);
	}

	NewTaskDialog::~NewTaskDialog()
	{
		if (m_newTaskInfoSetWidget != nullptr) {
			delete  m_newTaskInfoSetWidget;
			m_newTaskInfoSetWidget = nullptr;
		}

		if (m_treeView != nullptr) {
			delete  m_treeView;
			m_treeView = nullptr;
		}

		if (m_treeModel != nullptr) {
			delete  m_treeModel;
			m_treeModel = nullptr;
		}

		if (m_fileRootNode != nullptr) {
			delete  m_fileRootNode;
			m_fileRootNode = nullptr;
		}
	}

	void NewTaskDialog::init()
	{
		m_newTaskInfoSetWidget = new NewTaskInfoSetWidget();

		QWidget *originalFileManageWidget = new QWidget();
		{
			m_treeView = new Base::RTreeView();
			m_treeView->setFocusPolicy(Qt::FocusPolicy::NoFocus);
			m_treeView->setObjectName("mainWidget");
			connect(m_treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(slotTreeItemClicked(QModelIndex)));

			m_treeModel = new Base::RTreeModel();
			QStringList headList;
			headList << QStringLiteral("�ļ��ṹ");
			m_treeModel->setHeaderData(headList);

			m_treeView->setModel(m_treeModel);
			//�ļ�¼��
			m_fileLineEdit = new QLineEdit();

			m_fileButt = new Base::RIconButton();
			m_fileButt->setText(QStringLiteral("ѡ���ļ�"));
			m_fileButt->setMinimumSize(60, 30);
			connect(m_fileButt, SIGNAL(clicked()), this, SLOT(slotSeleteFile()));

			QWidget *filePathWidget = new QWidget();
			QHBoxLayout *hLayout = new QHBoxLayout();
			hLayout->addWidget(m_fileLineEdit);
			hLayout->addWidget(m_fileButt);
			filePathWidget->setLayout(hLayout);

			QVBoxLayout *originalFileManageLayout = new QVBoxLayout();
			originalFileManageLayout->addWidget(m_treeView);
			originalFileManageLayout->addWidget(filePathWidget);
			originalFileManageLayout->setContentsMargins(0, 4, 4, 4);
			originalFileManageWidget->setLayout(originalFileManageLayout);
		}

		QWidget *mainWidget = new QWidget();
		QHBoxLayout * mainLayout = new QHBoxLayout();
		mainLayout->addWidget(m_newTaskInfoSetWidget);
		mainLayout->addWidget(originalFileManageWidget);
		mainLayout->setContentsMargins(4, 4, 4, 4);
		mainWidget->setLayout(mainLayout);
		this->setContentWidget(mainWidget);

		setButton(DialogProxy::Ok, this, SLOT(respOk()));
		setButton(DialogProxy::Cancel, this, SLOT(reject()));
	}

	bool NewTaskDialog::FindFile(const QString & path)
	{
		QDir dir(path);
		if (!dir.exists()) {
			return false;
		}
		dir.setFilter(QDir::Dirs | QDir::Files);
		dir.setSorting(QDir::DirsFirst);
		QFileInfoList list = dir.entryInfoList();
		int i = 0;

		bool bIsDir;
		do {
			QFileInfo fileInfo = list.at(i);
			if (fileInfo.fileName() == "." | fileInfo.fileName() == "..") {
				++i;
				continue;
			}
			bIsDir = fileInfo.isDir();
			if (bIsDir) {
				Base::TreeNode *tempNode = createTreeNode(m_fileRootNode ,fileInfo.filePath());
				m_fileRootNode->nodes.append(tempNode);
				FindFile(fileInfo.filePath());
			}	
			else  {
				QString filePath = fileInfo.path();
				QFileInfo t_dirFileInfo(filePath);
				QString t_dirName = t_dirFileInfo.baseName();

				if (m_fileRootNode->nodes.size() > 0) {
					for (int i = 0; i < m_fileRootNode->nodes.size();i++) {
						Base::TreeNode * tempNode = m_fileRootNode->nodes.at(i);
						if (tempNode->nodeName == t_dirName) {
							Base::TreeNode *tempNode2 = createTreeNode(tempNode, fileInfo.filePath());
							tempNode->nodes.append(tempNode2);
						}
					}
				}
			}
			++i;
		} while (i < list.size());

		return true;
	}

	/*!
	 *  @brief �������ڵ�
	 */
	Base::TreeNode * NewTaskDialog::createTreeNode(Base::TreeNode * parentNode, QString  pasth)
	{
		QFileInfo t_fileInfo(pasth);

		Base::TreeNode * node = new Base::TreeNode;
		node->nodeChecked = false;
		node->nodeName = t_fileInfo.baseName();
		node->parentNode = parentNode;
		// �ļ�������Ϣ
		OriginalDataFileParameter * t_fileParameter = new OriginalDataFileParameter();
		t_fileParameter->name		= t_fileInfo.baseName();
		t_fileParameter->path		= pasth;
		t_fileParameter->createTime = t_fileInfo.created().toString("yyyy-MM-d hh:mm:ss");
		t_fileParameter->isDir		= t_fileInfo.isDir();
		node->nodeData = t_fileParameter;
		return node;
	}

	/*!
	 * @brief   ˢ��ģ��
	 * @details 
	 */
	void NewTaskDialog::updateModel()
	{
		m_treeModel->refreshModel();
		m_treeView->expandAll();
	}

	void NewTaskDialog::slotSeleteFile()
	{
		m_originalFilePath =  QFileDialog::getExistingDirectory(this, QStringLiteral("ѡ��Ŀ¼"),
			"./",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
		m_fileLineEdit->setText(m_originalFilePath);

		Base::TreeNode * parentNode = nullptr;
		m_fileRootNode = createTreeNode(parentNode, m_originalFilePath);

		FindFile(m_originalFilePath);

		m_treeModel->addRootNode(m_fileRootNode);

		this->updateModel();
	}

	void NewTaskDialog::slotTreeItemClicked(QModelIndex index)
	{
		Base::TreeNode * treeNode = static_cast<Base::TreeNode *>(index.internalPointer());
		OriginalDataFileParameter * t_fileParameter = static_cast<OriginalDataFileParameter *>(treeNode->nodeData);

		this->updateModel();
	}

	void NewTaskDialog::respOk()
	{
		// ���������Ϣ
		m_taskBaseInfo = m_newTaskInfoSetWidget->getTaskBaseInfo();
		sendTaskBaseInfo();
		//[] ��ȡ�ļ��б�
		m_taskDataFilePaths.clear();
		getFileNode(m_fileRootNode);
		sendTaskOriginalDataInfo();
		emit signalCreaateNewTask();

		respCancel();
	}

	void NewTaskDialog::respCancel() 
	{
		close();
	}
	
	bool NewTaskDialog::getFileNode(Base::TreeNode *node)
	{
		if (node == nullptr) {
			return false;
		}

		if (node->nodes.size() == 0){
			return false;
		}

		for (int i = 0; i < node->nodes.size(); i++)
		{
			Base::TreeNode *t_temp = node->nodes.at(i);
			OriginalDataFileParameter * t_fileParameter = static_cast<OriginalDataFileParameter *>(t_temp->nodeData);

			if (t_temp->nodes.size() > 0) {
				this->getFileNode(t_temp);
			} 
			else
			{
				//if (t_temp->nodeChecked == true) {
				qDebug() << t_fileParameter->createTime << t_fileParameter->path << t_fileParameter->name;
			//	}
				m_taskDataFilePaths.append(t_fileParameter);
			}
		}

		return true;
	}

	/*!
	 * @brief    ��������Ļ�����Ϣ
	 * @details 
	 */
	void NewTaskDialog::sendTaskBaseInfo()
	{
		Datastruct::DutyRecordCreateRequest request;
		request.taskId = m_taskBaseInfo.id;
		request.taskId = m_taskBaseInfo.taskName;
		NetConnector::instance()->write(request);
	}

	/*!
	 * @brief  �������������ļ��Ļ�����Ϣ
	 * @details 
	 */
	void NewTaskDialog::sendTaskOriginalDataInfo()
	{
	}

}//namespace Related 