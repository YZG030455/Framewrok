#include "customwidgetcontainer.h"

#include <QHBoxLayout>
#include <QPainter>

namespace Related {

	CustomWidgetContainer::CustomWidgetContainer(QWidget *parent)
		: QWidget(parent)
	{
		setObjectName("CustomWidgetContainer");
		init();
	}

	CustomWidgetContainer::~CustomWidgetContainer()
	{
	}

	void CustomWidgetContainer::setContent(QWidget * widget)
	{
		if (layout() == nullptr) {
			QHBoxLayout * hlayout = new QHBoxLayout();
			hlayout->setContentsMargins(4, 4, 4, 4);

			hlayout->addWidget(widget);
			setLayout(hlayout);
		}
		else {
			QHBoxLayout * hlayout = dynamic_cast<QHBoxLayout *>(layout());
			for (int i = hlayout->count(); i >= 0; i--) {
				hlayout->removeItem(hlayout->itemAt(i));
			}
			hlayout->addWidget(widget);
		}
	}

	void CustomWidgetContainer::paintEvent(QPaintEvent *event)
	{
		QPainter painter(this);

		QRect innerRect = rect();
		innerRect.adjust(1, 1, -1, -1);

		painter.setPen(Qt::NoPen);
		painter.setBrush(QColor(0, 64, 110, 80));
		painter.drawRect(innerRect);

		painter.setPen(QPen(QColor(118, 121, 124), 1.1));

		int radius = 8;

		//����
		painter.drawLine(innerRect.topLeft(), QPoint(1, radius));
		painter.drawLine(innerRect.topLeft(), QPoint(radius, 1));

		//����
		painter.drawLine(QPoint(innerRect.right() - radius, 1), innerRect.topRight());
		painter.drawLine(innerRect.topRight(), QPoint(innerRect.right(), radius));

		//����
		painter.drawLine(QPoint(1, innerRect.bottom() - radius), innerRect.bottomLeft());
		painter.drawLine(innerRect.bottomLeft(), QPoint(radius, innerRect.bottom()));

		//����
		painter.drawLine(QPoint(innerRect.right() - radius, innerRect.bottom()), innerRect.bottomRight());
		painter.drawLine(innerRect.bottomRight(), QPoint(innerRect.right(), innerRect.bottom() - radius));

		QWidget::paintEvent(event);
	}

	void CustomWidgetContainer::init()
	{

	}

} //namespace Related 