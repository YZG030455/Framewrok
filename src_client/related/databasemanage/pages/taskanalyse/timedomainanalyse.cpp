#include "timedomainanalyse.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimeEdit>
#include <QLine>

#include "../../customwidget/customwidgetcontainer.h"
#include "../../global.h"

namespace Related {

	TimeDomainAnalyse::TimeDomainAnalyse(QWidget *parent)
		: QWidget(parent)
	{
		init();
	}

	TimeDomainAnalyse::~TimeDomainAnalyse()
	{
	}

	PageType TimeDomainAnalyse::getPageType() const
	{
		return Page_TaskAnalyse_TimeDomainAnalysis;
	}

	void TimeDomainAnalyse::init()
	{
		auto createLabel = [](QString text) {
			QLabel * label = new QLabel();
			label->setText(text);
			return label;
		};

		auto createTimeEdit = []() {
			QTimeEdit * edit = new QTimeEdit();
			edit->setDisplayFormat("mm:ss:zzz");
			edit->setMinimumWidth(100);
			return edit;
		};

		auto createButt = [](QString icon) {
			Base::RIconButton * butt = new Base::RIconButton();
			butt->setIcon(QIcon(icon));
			butt->setFixedSize(26, 26);
			return butt;
		};

		auto createVerticalLine = []() {
			QFrame * line = new QFrame();
			line->setFixedWidth(1);
			line->setMinimumHeight(45);
			line->setStyleSheet("background-color:gray;");
			line->setFrameShape(QFrame::HLine);
			line->setFrameShadow(QFrame::Sunken);
			return line;
		};

		CustomWidgetContainer * wavEditContaienr = new CustomWidgetContainer();
		wavEditContaienr->setFixedHeight(85);
		{
			QWidget * toolWidget = new QWidget();
			QHBoxLayout * toolLayout = new QHBoxLayout();
			toolLayout->setContentsMargins(0, 0, 0, 0);
			toolLayout->setSpacing(20);
			toolWidget->setLayout(toolLayout);

			{
				Base::RIconButton * playButt = createButt(WRAP_RESOURCE_RADIO(����));
				Base::RIconButton * cutButt = createButt(WRAP_RESOURCE_RADIO(����));
				Base::RIconButton * endButt = createButt(WRAP_RESOURCE_RADIO(����));
				Base::RIconButton * pauseButt = createButt(WRAP_RESOURCE_RADIO(��ͣ));
				Base::RIconButton * forwardButt = createButt(WRAP_RESOURCE_RADIO(���));
				Base::RIconButton * backwardButt = createButt(WRAP_RESOURCE_RADIO(����));

				QLabel * cutStart = new QLabel();
				cutStart->setFixedWidth(60);
				cutStart->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
				cutStart->setText(QStringLiteral("��ʼʱ��"));

				QLabel * cutEnd = new QLabel();
				cutEnd->setFixedWidth(60);
				cutEnd->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
				cutEnd->setText(QStringLiteral("����ʱ��"));

				QHBoxLayout * tmpLayout = new QHBoxLayout();
				tmpLayout->setContentsMargins(0, 0, 0, 0);
				tmpLayout->addWidget(endButt);
				tmpLayout->addWidget(playButt);
				tmpLayout->addWidget(pauseButt);
				tmpLayout->addWidget(backwardButt);
				tmpLayout->addWidget(forwardButt);
				tmpLayout->addWidget(cutButt);
				tmpLayout->addStretch(1);

				toolLayout->addLayout(tmpLayout);
				toolLayout->addWidget(createVerticalLine());
			}

			{
				QLabel * currPalyTime = new QLabel();
				currPalyTime->setAlignment(Qt::AlignCenter);
				currPalyTime->setMinimumWidth(100);
				currPalyTime->setText("0:00:000");
				currPalyTime->setStyleSheet("font-size:19px;font-weight:600;");
				toolLayout->addWidget(currPalyTime);
				toolLayout->addWidget(createVerticalLine());
			}

			{
				QHBoxLayout * hlayout = new QHBoxLayout();
				hlayout->setContentsMargins(0, 0, 0, 0);

				Base::RIconButton * zoomOutButt = createButt(WRAP_RESOURCE_RADIO(��С));
				Base::RIconButton * zoomInButt = createButt(WRAP_RESOURCE_RADIO(�Ŵ�));

				hlayout->addWidget(zoomOutButt);
				hlayout->addWidget(zoomInButt);

				toolLayout->addLayout(hlayout);
				toolLayout->addWidget(createVerticalLine());
			}

			{
				QWidget * selectionArea = new QWidget();

				QGridLayout * glayout = new QGridLayout();
				glayout->setContentsMargins(0, 0, 0, 0);
				glayout->setVerticalSpacing(4);

				QLabel * startLabel = createLabel(QStringLiteral("��ʼ"));
				QLabel * endLabel = createLabel(QStringLiteral("����"));
				QLabel * lastLabel = createLabel(QStringLiteral("����ʱ��"));
				QLabel * viewLabel = createLabel(QStringLiteral("��ͼ"));
				QLabel * selectionLabel = createLabel(QStringLiteral("ѡȡ"));

				QTimeEdit * sectionStartTime = createTimeEdit();
				QTimeEdit * sectionEndTime = createTimeEdit();
				QTimeEdit * sectionLastTime = createTimeEdit();

				QTimeEdit * viewStartTime = createTimeEdit();
				QTimeEdit * viewEndTime = createTimeEdit();
				QTimeEdit * viewLastTime = createTimeEdit();

				glayout->addWidget(startLabel, 0, 1, 1, 1);
				glayout->addWidget(endLabel, 0, 2, 1, 1);
				glayout->addWidget(lastLabel, 0, 3, 1, 1);

				glayout->addWidget(selectionLabel, 1, 0, 1, 1);
				glayout->addWidget(sectionStartTime, 1, 1, 1, 1);
				glayout->addWidget(sectionEndTime, 1, 2, 1, 1);
				glayout->addWidget(sectionLastTime, 1, 3, 1, 1);

				glayout->addWidget(viewLabel, 2, 0, 1, 1);
				glayout->addWidget(viewStartTime, 2, 1, 1, 1);
				glayout->addWidget(viewEndTime, 2, 2, 1, 1);
				glayout->addWidget(viewLastTime, 2, 3, 1, 1);

				selectionArea->setLayout(glayout);

				toolLayout->addWidget(selectionArea);
			}

			toolLayout->addStretch(1);

			QVBoxLayout * wavLayout = new QVBoxLayout();
			wavLayout->setSpacing(1);
			wavLayout->setContentsMargins(4, 4, 4, 4);

			wavLayout->addWidget(toolWidget);

			QWidget * tmpWidget = new QWidget();
			tmpWidget->setLayout(wavLayout);
			wavEditContaienr->setContent(tmpWidget);
		}

		CustomWidgetContainer * graphContaienr = new CustomWidgetContainer();
		graphContaienr->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

		QVBoxLayout * vlayout = new QVBoxLayout();
		vlayout->setContentsMargins(4, 4, 4, 4);
		vlayout->addWidget(wavEditContaienr);
		vlayout->addWidget(graphContaienr);

		this->setLayout(vlayout);
	}

} //namespace Related