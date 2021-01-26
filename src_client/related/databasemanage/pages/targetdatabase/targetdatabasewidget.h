/*!
 * @brief     Ŀ������  
 * @details   �ṩ
 * @author    yzg
 * @version   1.0
 * @date      2021.01.20 10:43:37
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
 
#pragma once

#include <QWidget>
#include <qstackedwidget.h>

#include <base\selfwidget\rtabwidget.h>
#include "../abstractpage.h"

#include "targetdatabasemanagepage.h"

namespace Related {

	class TargetDatabaseWidget : public AbstractPage
	{
		Q_OBJECT

	public:
		TargetDatabaseWidget(QWidget *parent = nullptr);
		~TargetDatabaseWidget();

		PageType getPageType() const;

	private:
		void init();

	private:
		Base::RTabWidget * m_tabWidget;

		TargetDatabaseManagePage *m_targetDatabaseManagePage;
	};

}//namespace Related 