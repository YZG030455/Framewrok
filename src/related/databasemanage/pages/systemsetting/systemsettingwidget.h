/*!
 *  @brief     ϵͳ����ҳ��
 *  @details   �ṩ���û���Ϣ����ϵͳ���õȲ���
 *  @author    wey
 *  @version   1.0
 *  @date      2021.01.07
 *  @warning
 *  @copyright NanJing RenGu.
 *  @note
 */
#pragma once

#include <QWidget>
#include <qstackedwidget.h>

#include <base\selfwidget\rtabbar.h>
#include "../abstractpage.h"

#include "usermanagepage.h"
#include "othersettingpage.h"

namespace Related {

	class SystemSettingWidget : public AbstractPage
	{
		Q_OBJECT

	public:
		SystemSettingWidget(QWidget *parent = nullptr);
		~SystemSettingWidget();

		PageType getPageType() const;

		enum TabBarIndex {
			Tab_userManage,
			Tab_systemSetting,
		};

	private slots:
		void respTabChanged(int page);

	private:
		void init();

	private:
		Base::RTabBar * m_tabWidget;
		QStackedWidget * m_stackedWidget;

		UserManagePage * m_userManagePage;
		OtherSettingPage * m_otherSettingPage;
	};

} //namespace Related 