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

		void setImagesType(TestImagesType type);
		void setImagesIndex(int index);

	signals:
		void signalSeleteImagesIndex(int index);

	protected:
 		void paintEvent(QPaintEvent *event);
		void mousePressEvent(QMouseEvent * event);

		void enterEvent(QEvent * event);
		void leaveEvent(QEvent * event);
	private:
		void  init();

	private:
		TestImagesType m_imagesType;		/*!< ͼƬ���� */
		int m_imagesIndex;					/*!< ͼƬ���� */

		QString  m_imagesPath;				/*!< ͼƬ·�� */
		bool m_imagesSuspension;
	};

}//namespace Related