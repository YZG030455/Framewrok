#include "taskanalysepage.h"

#include <QDebug>

#include "timedomainanalyse.h"
#include "dynamicgraphanalysis.h"
#include "demongraph.h"
#include "lofargraph.h"
#include "situationanalysis.h"

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

	void TaskAnalysePage::prepareBringToTop()
	{
		AbstractPage * cpage = dynamic_cast<AbstractPage *>(m_tabWidget->currentWidget());
		if (cpage)
			cpage->prepareBringToTop();
	}

	void TaskAnalysePage::setTaskId(QString taskId)
	{
		m_dataPreviewPage->setTaskId(taskId);
	}

	void TaskAnalysePage::slotOpenAudioDataPage(QString dataId) 
	{
		m_tabWidget->setSwitchWidget(m_audioDataWidget);
	}

	void TaskAnalysePage::init()
	{
		m_tabWidget = new Base::RTabWidget();
		m_tabWidget->setTabBarHeight(60);

		{
			m_dataPreviewPage = new DataPreviewPage(this);
			connect(m_dataPreviewPage, SIGNAL(signalOpenAudioDataPage(QString)), 
				this, SLOT(slotOpenAudioDataPage(QString)));

			m_timeAnalyseWidget = new TimeDomainAnalyse(this);
			m_audioDataWidget = new DynamicGraphAnalysis(this);
			m_demonAnalysis = new DemonGraph(this);
			m_lofarAnalysis = new LofarGraph(this);
			m_situationAnalysis = new SituationAnalysis(this);
			m_ambientNoiseDataWidget = new AmbientNoiseDataWidget(this);
			m_hxjPlatformDataWidget = new HXJPlatformInfoWidget(this);

			m_tabWidget->addPage(QStringLiteral("����Ԥ��"),	m_dataPreviewPage);
			m_tabWidget->addPage(QStringLiteral("ʱ�����"),	m_timeAnalyseWidget);
			m_tabWidget->addPage(QStringLiteral("Ƶ�����"),	m_audioDataWidget);
			m_tabWidget->addPage(QStringLiteral("DEMON����"), m_demonAnalysis);
			m_tabWidget->addPage(QStringLiteral("LOFAR����"), m_lofarAnalysis);
			m_tabWidget->addPage(QStringLiteral("̬�Ʒ���"), m_situationAnalysis);
			m_tabWidget->addPage(QStringLiteral("��������"),	m_ambientNoiseDataWidget);
			m_tabWidget->addPage(QStringLiteral("HXJƽ̨��Ϣ"), m_hxjPlatformDataWidget);
		
			m_tabWidget->setWidgetBringToBottomCallback([&](QWidget * preWidet) {
				AbstractPage * preparePage = dynamic_cast<AbstractPage *>(preWidet);
				if (preparePage)
					preparePage->prepareBringToBottom();
			});

			m_tabWidget->setWidgetBringToTopCallback([&](QWidget * newWidet) {
				AbstractPage * nextPage = dynamic_cast<AbstractPage *>(newWidet);
				if (nextPage)
					nextPage->prepareBringToTop();
			});
		}

		QVBoxLayout * layout = new QVBoxLayout();
		layout->setContentsMargins(0, 0, 0, 0);
		layout->addWidget(m_tabWidget);
		setLayout(layout);
	}

} //namespace Related 