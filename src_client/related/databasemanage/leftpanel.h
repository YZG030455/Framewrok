/*!
 *  @brief     ����������
 *  @details   �������������б���������û������������
 *  @author    wey
 *  @version   1.0
 *  @date      2021.01.07
 *  @warning
 *  @copyright NanJing RenGu.
 *  @note
 */
#pragma once

#include <QWidget>
#include <qlabel.h>

#include <base\selfwidget\iconbutton.h>
#include <base\util\widgetanimation.h>

namespace Related {

	class RListWidget;

	class LeftPanel : public QWidget
	{
		Q_OBJECT

	public:
		LeftPanel(QWidget *parent);
		~LeftPanel();

	signals:
		void currentIndexChanged(int);

	private slots:
		void respLeftPanelExpand(bool checked);

	private:
		void init();

	private:
		RListWidget * m_listWidget;
		
		Base::WidgetAnimation m_animation;

		QLabel * m_prgoramIcon;
		Base::RIconButton * m_expandButt;
		int m_expandStateWidth;		//չ��״̬�¿��
		int m_contractionWidth;		//����״̬�¿��

		Base::RIconButton * m_notifyButt;
	};

} //namespace Related 
