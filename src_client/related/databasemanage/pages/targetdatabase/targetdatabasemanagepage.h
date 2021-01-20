/*!
 * @brief     目标管理页面      
 * @details   支持目标库的增加、删除、修改、同步
 * @author    yzg
 * @version   1.0
 * @date      2021.01.20 11:11:36
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
 
#pragma once

#include <QWidget>
#include <QComboBox>

#include <base\selfwidget\tablemode\rtableview.h>
#include <base\selfwidget\iconbutton.h>

#include "customwidget/operationtoolspage.h"
#include "tablemodel/targetdatabasemanagemodel.h"

namespace Related {

	class TargetDatabaseManagePage : public QWidget
	{
		Q_OBJECT

	public:
		TargetDatabaseManagePage(QWidget *parent = nullptr);
		~TargetDatabaseManagePage();


	private:
		void init();

	private:
		Base::RTableView * m_tableView;
		TargetDatabaseManageModel *m_tableModel;
		OperationToolsPage *m_operationToolsPage;
	};

}//namespace Related 
