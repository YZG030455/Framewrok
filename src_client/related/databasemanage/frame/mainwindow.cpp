#include "mainwindow.h"

#include <QDebug>
#include <qboxlayout.h>

#include "leftpanel.h"

namespace Related {

	MainWindow::MainWindow(QWidget *parent)
		: QWidget(parent)
	{
		init();
		initConnect();
	}

	MainWindow::~MainWindow()
	{
	}

	void MainWindow::init()
	{
		m_stackedWidget = new QStackedWidget();
		m_stackedWidget->setObjectName("Widget_MainWidow");

		//��¼ҳ��
		m_loginPage = new LoginPage();
		connect(m_loginPage, SIGNAL(switchToMainPage()), this, SLOT(respLoginSuccess()));

		m_mainWidget = new QWidget();

		{
			m_leftPanel = new LeftPanel(m_mainWidget);

			m_pageContainer = new QStackedWidget(m_mainWidget);
			m_pageContainer->setObjectName("Widget_RightPanel");

			//ϵͳ��ҳ
			m_mainPage = new SystemMainPage();
			m_mainPage->prepareBringToTop();

			//���ݹ���
			m_dataMangePage = new DataManageWidget();

			//ϵͳ����
			m_systemSettingPage = new SystemSettingWidget();

			//�������
			m_taskOverViewPage = new TaskOverViewPage();

			//�����¼
			m_taskRecordPage = new TaskRecordPage();

			//�������
			m_taskAnalysePage = new TaskAnalysePage();

			//Ŀ������
			m_targetDatabaseWidget = new TargetDatabaseWidget();

			QList<AbstractPage *> pages;
			pages << m_mainPage << m_dataMangePage << m_targetDatabaseWidget << m_systemSettingPage 
				<< m_taskOverViewPage << m_taskRecordPage << m_taskAnalysePage;

			for (AbstractPage * page : pages) {	
				m_pageContainer->addWidget(page);
				m_pageMapping.insert(page->getPageType(), page);
			}

			QHBoxLayout * mainLayout = new QHBoxLayout();
			mainLayout->setSpacing(0);
			mainLayout->setContentsMargins(0, 0, 0, 0);
			mainLayout->addWidget(m_leftPanel);
			mainLayout->addWidget(m_pageContainer);
			m_mainWidget->setLayout(mainLayout);
		}

		m_stackedWidget->addWidget(m_loginPage);
		m_stackedWidget->addWidget(m_mainWidget);

		QHBoxLayout * layout = new QHBoxLayout();
		layout->setContentsMargins(0, 0, 0, 0);
		layout->addWidget(m_stackedWidget);
		setLayout(layout);
	}

	void MainWindow::initConnect()
	{
		connect(m_leftPanel, SIGNAL(currentIndexChanged(int)), this, SLOT(switchPage(int)));
		connect(m_leftPanel, SIGNAL(switchToSystemView()), this, SLOT(switchToSystemView()));
		connect(m_mainPage, SIGNAL(openTask(QString)), this, SLOT(siwtchToTaskView(QString)));
	}

	void MainWindow::respLoginSuccess()
	{
		m_stackedWidget->setStyleSheet("#Widget_MainWidow{border-image:none;background-color: rgba(4,59,100, 235)}");
		m_stackedWidget->style()->unpolish(m_stackedWidget);
		m_stackedWidget->style()->polish(m_stackedWidget);
		m_stackedWidget->setCurrentWidget(m_mainWidget);
	}

	void MainWindow::switchPage(int pageIndex)
	{
		PageType pt = static_cast<PageType>(pageIndex);
		if (m_pageMapping.contains(pt)) {

			AbstractPage * prePage = dynamic_cast<AbstractPage *>(m_pageContainer->currentWidget());
			if (prePage)
				prePage->prepareBringToBottom();

			AbstractPage * nextPage = m_pageMapping.value(pt);
			nextPage->prepareBringToTop();

			m_pageContainer->setCurrentWidget(nextPage);
		}
	}

	/*!
	 * @brief �л���������ͼ������ȡָ����������Ϣ
	 * @param taskId ���򿪵�����ID
	 */
	void MainWindow::siwtchToTaskView(QString taskId)
	{
		m_taskOverViewPage->setTaskId(taskId);
		m_taskRecordPage->setTaskId(taskId);

		m_leftPanel->switchViewModel(TaskView);
		switchPage(m_leftPanel->getCurrentPage());
	}

	/*!
	 * @brief �л���ϵͳ����ҳ�棬�ָ���ҳ��ʾ
	 */
	void MainWindow::switchToSystemView()
	{
		switchPage(m_leftPanel->getCurrentPage());
	}

} //namespace Related 
