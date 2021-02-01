/*!
 * @brief     ����ͼƬ
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
#include <QPaintEvent>
#include <QMouseEvent>

namespace Related {

	class TestImagesItem : public QWidget
	{
		Q_OBJECT

	public:
		TestImagesItem(QWidget *parent = nullptr);
		~TestImagesItem();

		enum TestImagesType{
			TI_Sketch,				/*!< ��ͼ*/
			TI_Detail				/*!< ��ͼ */
		};

		void setImagesType(int inde);

	signals:
		void signalSeleteImagesIndex(int index);

	protected:
 		void paintEvent(QPaintEvent *event);
		void mouseDoubleClickEvent(QMouseEvent * event);

	private:
		void  init();

	private:
		int m_imagesIndex;					/*!< ͼƬ���� */
		QString  m_imagesPath;				/*!< ͼƬ·�� */
	};

}//namespace Related