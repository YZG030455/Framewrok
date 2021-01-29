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
#include <QLabel>
#include <QStackedWidget>

#include <base\selfwidget\iconbutton.h>
#include <base\util\widgetanimation.h>

#include "../datastruct.h"

namespace Related {

	class RListWidget;

	class LeftPanel : public QWidget
	{
		Q_OBJECT

	public:
		LeftPanel(QWidget *parent);
		~LeftPanel();

		/*!
		 * @brief �л����˵���ָ��ģʽ
		 * @note Ĭ����ʾ��һ���˵���
		 * @param model ���л�����ʾģʽ
		 */
		void switchViewModel(ViewModel model);

		int getCurrentPage() const;

	signals:
		void currentIndexChanged(int);
		void switchToSystemView();
		void reConnectToServer();

	private slots:
		void respNetStateChanged(bool isConnectToServer);
		void respLeftPanelExpand(bool checked);
		void backToSystemView();

	private:
		void init();

	private:
		RListWidget * m_systemListWidget;	/*!< ϵͳ�˵��б� */	
		RListWidget * m_taskListWidget;		/*!< ����˵��б� */
		QStackedWidget * m_leftMenuContainer;

		ViewModel m_currViewModel;			/*!< ��ǰ��ͼģʽ */
		
		Base::WidgetAnimation m_animation;

		QLabel * m_prgoramIcon;
		Base::RIconButton * m_expandButt;
		int m_expandStateWidth;		//չ��״̬�¿��
		int m_contractionWidth;		//����״̬�¿��

		Base::RIconButton * m_notifyButt;		/*!< ֪ͨ */
		Base::RIconButton * m_netStateButt;		/*!< ����״̬֪ͨ */
		Base::RIconButton * m_backToSystemViewButt;		/*!< ����ϵͳ��ͼ */
	};

} //namespace Related 
