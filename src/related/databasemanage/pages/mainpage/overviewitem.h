/*!
 *  @brief     ���ݸ�����ʾ��
 *  @details   �Խϴ�����塢����������ɫ��ʾ��Ҫ��Ϣ�����ڿ�ͨ������鿴��ϸ����
 *  @author    wey
 *  @version   1.0
 *  @date      2021.01.07
 *  @warning
 *  @copyright NanJing RenGu.
 *  @note
 */
#pragma once

#include <QWidget>
#include "ui_overviewitem.h"

namespace Related {

	class OverViewItem : public QWidget
	{
		Q_OBJECT

	public:
		OverViewItem(QWidget *parent = Q_NULLPTR);
		~OverViewItem();

		void setLabelText(QString  text);
		void setLabelData(QString text);
		void setLabelIcon(QString icon);
		void setLabelBackground(QColor color);

	private:
		Ui::OverViewItem ui;
	};

} //namespace Related 