/*!
 * @brief     �Զ���Tab����
 * @details	  ����RTabBar + QStackedWidgetʵ��
 * @author    wey
 * @version   1.0
 * @date      2021.01.26 10:37:27
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
 #pragma once

#include <functional>

#include <QWidget>
#include <QStackedWidget>

#include "../base_global.h"
#include "rtabbar.h"

namespace Base {

	class BASESHARED_EXPORT RTabWidget : public QWidget
	{
		Q_OBJECT

	public:
		RTabWidget(QWidget *parent = nullptr);
		~RTabWidget();

		void addPage(QString tabName,QWidget * widget);
		int pageCount() const;

		QWidget * currentWidget();

		void setTabBarHeight(int fixedHeight);
		int tabBarHeight() const;

		void setSpacing(int spacing);
		void setContentMargins(int left,int top,int right,int bottom);

		void setTabAligment(TabAlignment alignment);

		typedef std::function<void(QWidget *)> WidgetCallback;

		/*! 
		 * @brief ����StackedWidget�е�ǰ���ڱ��л����ײ�ʱ�ص��ӿ�
		 * @details �����ڹرյ�ǰҳ����δ��ɵ����������ҳ����ʾ��
		 * @param callback �ص�����
		 */
		void setWidgetBringToBottomCallback(WidgetCallback callback);

		/*!
		 * @brief ����StackedWidget���´��ڱ��л���������ʾʱ�ص��ӿ�
		 * @details �������´��ڵĳ�ʼ�������һ�η��������
		 * @param callback �ص�����
		 */
		void setWidgetBringToTopCallback(WidgetCallback callback);

	private slots:
		void prepareSwitchWidget(int index);

	private:
		void init();

	private:
		RTabBar * m_tabBar;
		QStackedWidget * m_widgetContainer;

		WidgetCallback m_bingToBottomCallback;		
		WidgetCallback m_bringToTopCallback;	
	};

} //namespace Base 