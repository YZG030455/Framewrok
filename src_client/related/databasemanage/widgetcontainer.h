/*!
 *  @brief     ��ҳ�洰����
 *  @details   ��������ʽ���ѵ��������ҳ�棬ͨ�������б�ɽ����л���
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
#include <qmap.h>

#include "pages\mainpage\mainpage.h"
#include "pages\databasemanage\datamanagewidget.h"
#include "pages\systemsetting\systemsettingwidget.h"

namespace Related {

	class WidgetContainer : public QWidget
	{
		Q_OBJECT

	public:
		WidgetContainer(QWidget *parent);
		~WidgetContainer();

	private slots:
		void switchPage(int pageIndex);

	private:
		void init();
		void initPages();

	private:
		QStackedWidget * m_stackedWidget;

		MainPage * m_mainPage;
		DataManageWidget * m_dataMangePage;
		SystemSettingWidget * m_systemSettingPage;

		QMap<PageType, AbstractPage *> m_pageMapping;
	};
} //namespace Related 