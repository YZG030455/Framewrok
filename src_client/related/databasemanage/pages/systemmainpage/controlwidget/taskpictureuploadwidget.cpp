#include "taskpictureuploadwidget.h"

namespace Related {

	TaskPictureUploadWidget::TaskPictureUploadWidget(QWidget *parent)
		: QWidget(parent)
	{

	}

	TaskPictureUploadWidget::~TaskPictureUploadWidget()
	{
	}

	void TaskPictureUploadWidget::paintEvent(QPaintEvent * event)
	{
		//[] ����ͼƬ
		QPainter painter(this);
		QPixmap pix;
		painter.translate(0, 0);
		pix.load(m_picturePath);
		painter.drawPixmap(5, 5, width() - 10, height() - 10, pix);

		painter.setRenderHint(QPainter::Antialiasing, true);
		painter.setPen(QColor(119,136,153));
		painter.drawRect(3, 3, width() - 6, height() - 6);
		QWidget::paintEvent(event);
	}

	void TaskPictureUploadWidget::mousePressEvent(QMouseEvent * event)
	{
		// ������
		if (event->button() == Qt::LeftButton) {

// 			QFileDialog *t_fileDialog = new QFileDialog(this);
// 			t_fileDialog->setWindowTitle(QStringLiteral("���ļ�"));
// 			t_fileDialog->setDirectory(".");
// 			t_fileDialog->setNameFilter(QStringLiteral("*(*.*)"));
// 			t_fileDialog->setViewMode(QFileDialog::Detail);
// 			if (t_fileDialog->exec()){
// 				m_picturePath = t_fileDialog->getOpenFileName();
// 				this->update();
// 			}
			
			m_picturePath = QFileDialog::getOpenFileName(NULL, QStringLiteral("ѡ���ļ�"), ".", "*.*");
			if(!m_picturePath.isEmpty()) {
				this->update();
			}
		}
	}

	void TaskPictureUploadWidget::init()
	{
	}

}//namespace Related 
