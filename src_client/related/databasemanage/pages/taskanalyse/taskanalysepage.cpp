#include "taskanalysepage.h"

#include <QDebug>

namespace Related {

	TaskAnalysePage::TaskAnalysePage(QWidget *parent)
		: AbstractPage(parent)
	{
		init();
	}

	TaskAnalysePage::~TaskAnalysePage()
	{
	}

	Related::PageType TaskAnalysePage::getPageType() const
	{
		return Page_TaskDataAnalyse;
	}

	void TaskAnalysePage::init()
	{
		m_tabWidget = new Base::RTabWidget();
		m_tabWidget->setTabBarHeight(60);

		// ҵ����ʾ����
		{
			m_dataOverviewWidget = new DataOverviewWidget(this);

			m_audioDataWidget = new AudioDataWidget(this);

			m_ambientNoiseDataWidget = new AmbientNoiseDataWidget(this);

			m_hxjPlatformDataWidget = new HXJPlatformInfoWidget(this);

			m_tabWidget->addPage(QStringLiteral("����Ԥ��"), m_dataOverviewWidget);
			m_tabWidget->addPage(QStringLiteral("��Ƶ��Ϣ"), m_audioDataWidget);
			m_tabWidget->addPage(QStringLiteral("��������"), m_ambientNoiseDataWidget);
			m_tabWidget->addPage(QStringLiteral("HXJƽ̨��Ϣ"), m_hxjPlatformDataWidget);
		}

		QVBoxLayout * layout = new QVBoxLayout();
		layout->setContentsMargins(0, 0, 0, 0);
		layout->addWidget(m_tabWidget);
		setLayout(layout);
	}

} //namespace Related 