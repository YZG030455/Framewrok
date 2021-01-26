#include "taskrecordpage.h"

namespace Related {

	TaskRecordPage::TaskRecordPage(QWidget *parent)
		: AbstractPage(parent)
	{
		init();
	}

	TaskRecordPage::~TaskRecordPage()
	{
	}

	Related::PageType TaskRecordPage::getPageType() const
	{
		return Page_TaskRecordPage;
	}

	void TaskRecordPage::init()
	{
		m_tabWidget = new Base::RTabWidget();
		m_tabWidget->setTabBarHeight(60);

		m_logbookPage = new LogbookPage();

		m_trialSheetWidget = new TrialSheetWidget();

		m_taskReportsWidget = new TaskReportsWidget();

		m_tabWidget->addPage(QStringLiteral("ֵ����־��"), m_logbookPage);
		m_tabWidget->addPage(QStringLiteral("�����¼��"), m_trialSheetWidget);
		m_tabWidget->addPage(QStringLiteral("���񱨸�"), m_taskReportsWidget);

		QVBoxLayout * mainLayout = new QVBoxLayout();
		mainLayout->addWidget(m_tabWidget);
		mainLayout->setContentsMargins(0, 0, 0, 0);
		setLayout(mainLayout);
	}

} //namespace Related 