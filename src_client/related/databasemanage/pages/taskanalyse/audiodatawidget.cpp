#include "audiodatawidget.h"
#include "ui_wavfeature.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimeEdit>

#include <base\selfwidget\rtabwidget.h>
#include "../../utils/util.h"
#include "../../customwidget/pageswitchbar.h"
#include "../../customwidget/customwidgetcontainer.h"
#include "../../global.h"

namespace Related {

	WavDataPage::WavDataPage(QWidget *parent)
		: AbstractPage(parent)
	{
		m_wavFeatureUi = new Ui::WavFeature();
		init();
	}

	WavDataPage::~WavDataPage()
	{
	}

	PageType WavDataPage::getPageType() const
	{
		return Page_TaskAnalyse_WavData;
	}

	void WavDataPage::prepareBringToTop()
	{
	}

	void WavDataPage::init()
	{
		CustomWidgetContainer * wavEditContaienr = new CustomWidgetContainer();
		wavEditContaienr->setFixedHeight(80);
		{
			QWidget * toolWidget = new QWidget();
			toolWidget->setFixedHeight(26);

			{
				QHBoxLayout * tooLayout = new QHBoxLayout();
				tooLayout->setContentsMargins(0,0,0,0);

				auto createButt = [](QString icon) {
					Base::RIconButton * butt = new Base::RIconButton();
					butt->setIcon(QIcon(icon));
					butt->setFixedSize(26,26);
					return butt;
				};

				Base::RIconButton * playButt = createButt(WRAP_RESOURCE_RADIO(����));
				Base::RIconButton * zoomInButt = createButt(WRAP_RESOURCE_RADIO(�Ŵ�));
				Base::RIconButton * cutButt = createButt(WRAP_RESOURCE_RADIO(����));
				Base::RIconButton * endButt = createButt(WRAP_RESOURCE_RADIO(����));
				Base::RIconButton * zoomOutButt = createButt(WRAP_RESOURCE_RADIO(��С));
				Base::RIconButton * pauseButt = createButt(WRAP_RESOURCE_RADIO(��ͣ));	

				QLabel * cutStart = new QLabel();
				cutStart->setFixedWidth(60);
				cutStart->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
				cutStart->setText(QStringLiteral("��ʼʱ��"));

				QLabel * cutEnd = new QLabel();
				cutEnd->setFixedWidth(60);
				cutEnd->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
				cutEnd->setText(QStringLiteral("����ʱ��"));

				QString timeFormat("mm:ss:zzz");

				QTimeEdit * cutTime = new QTimeEdit();
				cutTime->setDisplayFormat(timeFormat);
				cutTime->setFixedWidth(95);

				QTimeEdit * endTime = new QTimeEdit();
				endTime->setDisplayFormat(timeFormat);
				endTime->setFixedWidth(95);


				tooLayout->addWidget(endButt);
				tooLayout->addWidget(playButt);
				tooLayout->addWidget(pauseButt);
				tooLayout->addWidget(zoomInButt);
				tooLayout->addWidget(zoomOutButt);
				tooLayout->addWidget(cutButt);
				tooLayout->addSpacing(10);

				tooLayout->addWidget(cutStart);
				tooLayout->addWidget(cutTime);
				tooLayout->addWidget(cutEnd);
				tooLayout->addWidget(endTime);

				tooLayout->addStretch(1);

				toolWidget->setLayout(tooLayout);
			}

			QWidget * wavGraphWidget = new QWidget();
			wavGraphWidget->setFixedHeight(53);

			QVBoxLayout * wavLayout = new QVBoxLayout();
			wavLayout->setSpacing(1);
			wavLayout->setContentsMargins(4, 4, 4, 4);

			wavLayout->addWidget(toolWidget);
			wavLayout->addWidget(wavGraphWidget);

			QWidget * tmpWidget = new QWidget();
			tmpWidget->setLayout(wavLayout);
			wavEditContaienr->setContent(tmpWidget);
		}

		CustomWidgetContainer * graphContaienr = new CustomWidgetContainer();
		{
			Base::RTabBar * tabBar = new Base::RTabBar();
			tabBar->setFixedHeight(40);
			tabBar->setTabAlignment(Base::AlignCenter);
			tabBar->addTabButton(QStringLiteral("Demon��ͼ"), P_DEMON);
			tabBar->addTabButton(QStringLiteral("Lofar��ͼ"), P_LOFAR);
			tabBar->addTabButton(QStringLiteral("̬����Ϣ��ͼ"), P_MAP);
			tabBar->addTabButton(QStringLiteral("AIS����"), P_AIS);

			m_pageContainer = new QStackedWidget();

			//DEMON
			QWidget * demonWidget = new QWidget();
			{

			}

			//LOFAR
			QWidget * lofarWidget = new QWidget();
			{

			}

			//̬����Ϣ
			QWidget * mapWidget = new QWidget();
			{

			}

			//AIS��Ϣ
			QWidget * aisWidget = new QWidget();
			{

			}

			m_pageContainer->addWidget(demonWidget);
			m_pageContainer->addWidget(lofarWidget);
			m_pageContainer->addWidget(mapWidget);
			m_pageContainer->addWidget(aisWidget);

			connect(tabBar, SIGNAL(currentIndexChanged(int)), m_pageContainer, SLOT(setCurrentIndex(int)));

			//������Ϣ
			m_wavFeatureWidget = new QWidget();
			m_wavFeatureWidget->setFixedWidth(250);
			{
				m_wavFeatureUi->setupUi(m_wavFeatureWidget);
			}

			QHBoxLayout * layout = new QHBoxLayout();
			layout->setContentsMargins(0, 0, 0, 0);
			layout->addWidget(m_pageContainer);
			layout->addWidget(m_wavFeatureWidget);

			QWidget * tmpWidget = new QWidget();
			QVBoxLayout * tmpLayout = new QVBoxLayout();
			tmpLayout->setContentsMargins(0, 0, 0, 0);
			tmpLayout->addWidget(tabBar);
			tmpLayout->addLayout(layout);
			tmpWidget->setLayout(tmpLayout);

			graphContaienr->setContent(tmpWidget);
		}

		QVBoxLayout * mainlayout = new QVBoxLayout();
		mainlayout->addWidget(wavEditContaienr);
		mainlayout->addWidget(graphContaienr);
		mainlayout->setContentsMargins(4, 4, 4, 4);
		setLayout(mainlayout);
	}

}//namespace Related 