#include "taskoverviewpage.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QDateTime>
#include <QListView>

#include "../../customwidget/customwidgetcontainer.h"


namespace Related {

	TaskOverViewPage::TaskOverViewPage(QWidget *parent)
		: AbstractPage(parent)
	{
	
		init();

		updateTaskInfo();
	}

	TaskOverViewPage::~TaskOverViewPage()
	{
	}

	Related::PageType TaskOverViewPage::getPageType() const
	{
		return Page_TaskOverviewPage;
	}

	void TaskOverViewPage::updateTaskInfo()
	{
		TaskBaseInfo t_info;
		t_info.id			= QStringLiteral("����01");					
		t_info.taskName		= QStringLiteral("����01");			
		//t_info.taskTime		= QStringLiteral("2021-01-05 11:15:12");			
		t_info.taskplace	= QStringLiteral("�ൺ");			
		t_info.startTime	= QStringLiteral("2021-01-05 11:16:12");			
		t_info.endTime		= QStringLiteral("2021-01-05 19:15:12");			
		t_info.timeLength	= QStringLiteral("1500");	

		t_info.m_platformtype = 1;
		//
		m_taskBaseInfoPage->setTaskBaseInfo(t_info);

		//[] 
		PlatformInfos  platformInfos;

		m_taskResultInfoPage->setResultInfos(platformInfos);
	}

	void TaskOverViewPage::init()
	{
		// ����ͳ����Ϣ
		CustomWidgetContainer * taskStatisticsInfoContainer = new CustomWidgetContainer();
		{
			QSize maxSize(415, 170);
			QSize minSize(345, 170);
			m_taskPlatformType = new OverViewItem();
			m_taskPlatformType->setLabelData(QString::number(12));
			m_taskPlatformType->setLabelText(QStringLiteral("ƽ̨����"));
			m_taskPlatformType->setLabelBackground(QColor(237, 168, 27));
			m_taskPlatformType->setLabelIcon(QStringLiteral(":/QYBlue/resource/qyblue/�ϴ�.png"));
			m_taskPlatformType->setFixedSize(maxSize);
			m_taskPlatformType->setMinimumSize(minSize);

			m_platformdataSize = new OverViewItem();
			m_platformdataSize->setLabelData("120GB");
			m_platformdataSize->setLabelBackground(QColor(77, 174, 116));
			m_platformdataSize->setLabelText(QStringLiteral("ƽ̨ռ�ÿռ�"));
			m_platformdataSize->setLabelIcon(QStringLiteral(":/QYBlue/resource/qyblue/���ݿ��¼.png"));
			m_platformdataSize->setMaximumSize(maxSize);
			m_platformdataSize->setMinimumSize(minSize);

			m_advSize = new OverViewItem();
			m_advSize->setLabelData(QString::number(8));
			m_advSize->setLabelBackground(QColor(199, 99, 116));
			m_advSize->setLabelText(QStringLiteral("��Ƶ����ռ�ÿռ�"));
			m_advSize->setLabelIcon(QStringLiteral(":/QYBlue/resource/qyblue/δ����.png"));
			m_advSize->setMaximumSize(maxSize);
			m_advSize->setMinimumSize(minSize);

			QHBoxLayout * overViewLayout = new QHBoxLayout();
			overViewLayout->setContentsMargins(10, 15, 10, 15);
			overViewLayout->addWidget(m_taskPlatformType);
			overViewLayout->addWidget(m_platformdataSize);
			overViewLayout->addWidget(m_advSize);

			QWidget * tmpWidget = new QWidget();
			tmpWidget->setLayout(overViewLayout);
			taskStatisticsInfoContainer->setFixedHeight(maxSize.height() + overViewLayout->contentsMargins().top() + overViewLayout->contentsMargins().bottom());
			taskStatisticsInfoContainer->setContent(tmpWidget);
		}

		//[] ������ϸ��Ϣ����		
		CustomWidgetContainer * taskBaseInfoContainer = new CustomWidgetContainer();
		{
			m_taskBaseInfoPage = new TaskBaseInfoPage();
			m_taskBaseInfoPage->setMinimumHeight(200);
			m_taskBaseInfoPage->setMaximumHeight(240);

			QHBoxLayout *taskBaseInfoLayout = new QHBoxLayout();
			taskBaseInfoLayout->addWidget(m_taskBaseInfoPage);
			taskBaseInfoLayout->setContentsMargins(0, 0, 0, 0);
			taskBaseInfoContainer->setLayout(taskBaseInfoLayout);
		}
	
		//[]��������Ϣչʾ����
		CustomWidgetContainer * taskResultInfoContainer = new CustomWidgetContainer();
		{
			m_taskResultInfoPage = new TaskResultInfoPage();

			QHBoxLayout *taskResultInfoLayout = new QHBoxLayout();
			taskResultInfoLayout->addWidget(m_taskResultInfoPage);
			taskResultInfoLayout->setContentsMargins(0, 0, 0, 0);
			taskResultInfoContainer->setLayout(taskResultInfoLayout);
		}

		QWidget *mainwidget = new QWidget();
		QVBoxLayout *VLayout = new  QVBoxLayout();
		VLayout->addWidget(taskStatisticsInfoContainer);
		VLayout->addWidget(taskBaseInfoContainer);
		VLayout->addWidget(taskResultInfoContainer);
		VLayout->setContentsMargins(0, 0, 0, 0);
		mainwidget->setLayout(VLayout);
		
		QHBoxLayout *mainLayout = new QHBoxLayout();
		mainLayout->addWidget(mainwidget);
		mainLayout->setContentsMargins(4, 4, 4, 4);
		this->setLayout(mainLayout);
	}

} //namespace Related