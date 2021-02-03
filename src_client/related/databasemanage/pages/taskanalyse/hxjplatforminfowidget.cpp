#include "hxjplatforminfowidget.h"

#include <QDebug>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>

#include "../../utils/util.h"
#include "../../customwidget/customwidgetcontainer.h"
#include "../../customwidget/rcustomplot.h"

namespace Related {

	HXJPlatformInfoWidget::HXJPlatformInfoWidget(QWidget *parent)
		: AbstractPage(parent)
	{
		init();
	}

	HXJPlatformInfoWidget::~HXJPlatformInfoWidget()
	{

	}

	PageType HXJPlatformInfoWidget::getPageType() const
	{
		return PageType();
	}

	void HXJPlatformInfoWidget::prepareBringToTop()
	{
	}

	void HXJPlatformInfoWidget::init()
	{
		auto createCheckBox = [](QString boxName,int fixedWidth = 60) {
			QCheckBox * box = new QCheckBox;
			box->setFixedWidth(fixedWidth);
			box->setText(boxName);
			return box;
		};

		CustomWidgetContainer * typeContainer = new CustomWidgetContainer();
		{
			QWidget * dataTypeWidget = new QWidget();
			//dataTypeWidget->setFixedHeight(50);
			QLabel * typeLabel = new QLabel();
			typeLabel->setText(QStringLiteral("��������:"));

			QHBoxLayout * dataTypeLayout = new QHBoxLayout();
			dataTypeLayout->addWidget(typeLabel);
			dataTypeLayout->addWidget(createCheckBox(QStringLiteral("�¶�")));
			dataTypeLayout->addWidget(createCheckBox(QStringLiteral("ѹ��")));
			dataTypeLayout->addWidget(createCheckBox(QStringLiteral("���")));
			dataTypeLayout->addWidget(createCheckBox(QStringLiteral("�����")));
			dataTypeLayout->addWidget(createCheckBox(QStringLiteral("������")));
			dataTypeLayout->addWidget(createCheckBox(QStringLiteral("�����")));
			dataTypeLayout->addStretch(1);

			dataTypeWidget->setLayout(dataTypeLayout);

			typeContainer->setContent(dataTypeWidget);
		}

		CustomWidgetContainer * workContainer = new CustomWidgetContainer();
		{
			QWidget * workStateWidget = new QWidget();
			//workStateWidget->setFixedHeight(40);

			QLabel * typeLabel = new QLabel();
			typeLabel->setText(QStringLiteral("����״̬:"));

			QHBoxLayout * workLayout = new QHBoxLayout();
			workLayout->addWidget(typeLabel);
			workLayout->addWidget(createCheckBox(QStringLiteral("�ϸ�״̬"),90));
			workLayout->addWidget(createCheckBox(QStringLiteral("��Ǳ״̬"), 90));
			workLayout->addWidget(createCheckBox(QStringLiteral("ˮ�º���״̬"), 110));
			workLayout->addStretch(1);

			workStateWidget->setLayout(workLayout);
			workContainer->setContent(workStateWidget);
		}

		CustomWidgetContainer * container = new CustomWidgetContainer();
		container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		{
			RCustomPlot * plot = new RCustomPlot();
			container->setContent(plot);
		}

		QVBoxLayout * vlayout = new QVBoxLayout();
		vlayout->setContentsMargins(4, 4, 4, 4);
		vlayout->addWidget(typeContainer);
		vlayout->addWidget(workContainer);
		vlayout->addWidget(container);
		setLayout(vlayout);
	}

}//namespace Related 
