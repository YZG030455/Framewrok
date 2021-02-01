#include "taskresultitem.h"

#include <QDebug>
#include <QPainter>
#include <QPixmap>

namespace Related {

	TestImagesItem::TestImagesItem(QWidget *parent)
		: QWidget(parent),
		m_imagesIndex(0)
	{
		this->setMinimumSize(280, 270);
		this->setMaximumSize(300, 290);
		m_imagesPath = QStringLiteral(":/QYBlue/resource/qyblue/�����¼.png");

		init();
	}

	TestImagesItem::~TestImagesItem()
	{

	}

	void TestImagesItem::setImagesType(int inde)
	{
		m_imagesIndex = inde;
	}

	void TestImagesItem::paintEvent(QPaintEvent * event)
	{
		//[] ����ͼƬ
		QPainter painter(this);
		QPixmap pix;
		painter.translate(0, 0);
		 bool t_statue =	pix.load(m_imagesPath);
		painter.drawPixmap(5, 5, width()-10, height()-10, pix);//����ͼƬ �����ꡢ�����ꡢ��ȡ��߶�

		painter.setRenderHint(QPainter::Antialiasing, true);
		painter.setPen(QColor(0, 255, 255));
		painter.drawRect(3, 3, width()-6, height()-6);

		// ������Ϣ
		painter.setPen(QColor(255, 255, 255));
		painter.drawText(10, height() - 16, QStringLiteral("20210120 �����¼"));

		QWidget::paintEvent(event);
	}

	void TestImagesItem::mouseDoubleClickEvent(QMouseEvent * event)
	{
		if (event->button() == Qt::LeftButton)
		emit signalSeleteImagesIndex(m_imagesIndex);
	}

	void TestImagesItem::init()
	{
	}

}//namespace Related 