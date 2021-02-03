#include "taskoverviewpage.h"

#include <QDebug>

namespace Related {

	TaskOverViewPage::TaskOverViewPage(QWidget *parent)
		: AbstractPage(parent),
		m_firstLoadData(true)
	{
		init();
		initConnect();
		createTestImagesItem();
	}

	TaskOverViewPage::~TaskOverViewPage()
	{
	}

	Related::PageType TaskOverViewPage::getPageType() const
	{
		return Page_TaskOverviewPage;
	}

	void TaskOverViewPage::prepareBringToTop()
	{
		if (m_firstLoadData ) {
			refreshCurrTaskSimple();
			m_firstLoadData = false;
		}
	}

	void TaskOverViewPage::setTaskId(QString taskId) 
	{
		if (m_taskId.isEmpty()) {
			m_taskId = taskId;
		}
		else
		{
			if (m_taskId != taskId) {
				m_taskId = taskId;
				m_firstLoadData = true;
			}
		}
	}

	void TaskOverViewPage::processTaskSimpleResponse(const Datastruct::TaskSimpleResponse & response)
	{
		if (response.m_result == true) {
			m_taskBaseInfoPage->setTaskBaseInfo(response.taskInfo);
		}
	}

	void TaskOverViewPage::slotSelectedImagesIndex(int index)
	{
		TestImagesDetailDialog dialog(this);
		dialog.exec();

	}

	void TaskOverViewPage::init()
	{
		CustomWidgetContainer * taskStatisticsInfoContainer = new CustomWidgetContainer();
		{
			QSize maxSize(415, 170);
			QSize minSize(345, 170);
			m_taskPlatformType = new OverViewItem();
			m_taskPlatformType->setLabelData(QString::number(12));
			m_taskPlatformType->setLabelText(QStringLiteral("ƽ̨����"));
			m_taskPlatformType->setLabelBackground(QColor(237, 168, 27));
			m_taskPlatformType->setLabelIcon(WRAP_RESOURCE(�ϴ�));
			m_taskPlatformType->setFixedSize(maxSize);
			m_taskPlatformType->setMinimumSize(minSize);

			m_platformdataSize = new OverViewItem();
			m_platformdataSize->setLabelData("120GB");
			m_platformdataSize->setLabelBackground(QColor(77, 174, 116));
			m_platformdataSize->setLabelText(QStringLiteral("ƽ̨ռ�ÿռ�"));
			m_platformdataSize->setLabelIcon(WRAP_RESOURCE(���ݿ��¼));
			m_platformdataSize->setMaximumSize(maxSize);
			m_platformdataSize->setMinimumSize(minSize);

			m_advSize = new OverViewItem();
			m_advSize->setLabelData(QString::number(8));
			m_advSize->setLabelBackground(QColor(199, 99, 116));
			m_advSize->setLabelText(QStringLiteral("��Ƶ����ռ�ÿռ�"));
			m_advSize->setLabelIcon(WRAP_RESOURCE(δ����));
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
			m_testImagesScrollArea = new QScrollArea();
			m_testImagesScrollArea->setStyleSheet("background-color:rgba(0,0,0,0)");
			m_testImagesScrollArea->setWidgetResizable(true);

			m_testImagesWidget = new QWidget();
			m_testImagesWidget->setStyleSheet("background-color:rgba(0,0,0,0)");
			m_testImagesScrollArea->setWidget(m_testImagesWidget);

			QHBoxLayout *taskResultInfoLayout = new QHBoxLayout();
			taskResultInfoLayout->addWidget(m_testImagesScrollArea);
			taskResultInfoLayout->setContentsMargins(0, 0, 0, 0);
			taskResultInfoContainer->setLayout(taskResultInfoLayout);
		}

		QWidget *mainwidget = new QWidget();
		QVBoxLayout *VLayout = new  QVBoxLayout();
		VLayout->addWidget(taskStatisticsInfoContainer);
		VLayout->addWidget(taskBaseInfoContainer);
		VLayout->addWidget(taskResultInfoContainer);
		VLayout->setContentsMargins(0, 40, 0, 0);
		mainwidget->setLayout(VLayout);
		
		QHBoxLayout *mainLayout = new QHBoxLayout();
		mainLayout->addWidget(mainwidget);
		mainLayout->setContentsMargins(4, 4, 4, 4);
		this->setLayout(mainLayout);
	}

	void TaskOverViewPage::initConnect()
	{
		connect(SignalDispatch::instance(), SIGNAL(respTaskSimpleResponse(const Datastruct::TaskSimpleResponse &)),
			this, SLOT(processTaskSimpleResponse(const Datastruct::TaskSimpleResponse &)));
	}

	void TaskOverViewPage::updateTestImages()
	{
		QGridLayout * gLayout = nullptr;

		if (m_testImagesWidget->layout() == nullptr) {
			gLayout = new QGridLayout();
			gLayout->setContentsMargins(0, 0, 0, 0);
			m_testImagesWidget->setLayout(gLayout);
		}
		else {
			gLayout = dynamic_cast<QGridLayout *>(m_testImagesWidget->layout());
			for (int i = gLayout->count() - 1; i >= 0; i--) {
				if (gLayout->itemAt(i)->widget()) {
					delete gLayout->takeAt(i);
				}
			}
		}

		for (int i = 0; i < m_imagesItems.size(); i++) {
			int row = i / 5;
			int column = i % 5;
			gLayout->addWidget(m_imagesItems.at(i), row, column, 1, 1);
		}
	}

	void TaskOverViewPage::refreshCurrTaskSimple()
	{
		Datastruct::TaskSimpleRequest request;
		request.taskId = m_taskId;
		DataNetConnector::instance()->write(request);
	}

	void TaskOverViewPage::createTestImagesItem()
	{
		for (int i = 0; i < 15; i++ ) {
			TestImagesItem *item = new TestImagesItem();
			item->setImagesType(TestImagesItem::TI_Sketch);
			item->setImagesIndex(i + 1);
			item->setMinimumSize(280, 270);
			item->setMaximumSize(300, 290);
			connect(item, SIGNAL(signalSeleteImagesIndex(int)), this, SLOT(slotSelectedImagesIndex(int)));
			m_imagesItems.append(item);
		}
		updateTestImages();
	}

} //namespace Related