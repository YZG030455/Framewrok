/*!
 * @brief     ��������Ϣ
 * @details   ����������ʾ���ͼƬ
 * @author    yzg
 * @version   1.0
 * @date      2021.01.21 11:12:55
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
 
#pragma once

#include <QWidget>
#include <QMouseEvent>

namespace Related {

	class TaskResultItem : public QWidget
	{
		Q_OBJECT

	public:
		TaskResultItem(QWidget *parent = nullptr);
		~TaskResultItem();

		void setPictureIndex(int index);
		int getPictureIndex();

		void setPicturePath(QString path);
		QString getPicturePath();

		void setSelectedstatus(bool status);

		void updateItem();

		

	signals:
		void signalPictureIndex(int index, QString path);

	protected:
		void paintEvent(QPaintEvent *event);
		void mousePressEvent(QMouseEvent *event);

	private:
		void  init();

	private:
		int m_pictureIndex;					/*!< ͼƬ���� */
		QString  m_picturePath;				/*!< ͼƬ·�� */
		bool m_selectedstatus;				/*!< ���ѡ��״̬ */
	};

}//namespace Related