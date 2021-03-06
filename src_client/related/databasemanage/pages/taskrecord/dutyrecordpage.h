/*!
 * @brief     值班日志数据显示界面
 * @details   显示值班日志全部数据， 并对值班数据进行创建/编辑/删除等
 * @author    yzg
 * @version   1.0
 * @date      2021.01.20 19:39:23
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
#pragma once

#include <QWidget>
#include <QComboBox>
#include <QHBoxLayout>
#include <QItemSelectionModel>
#include <QAbstractItemModel>

#include <base\selfwidget\tablemode\rtableview.h>
#include <base\selfwidget\iconbutton.h>
#include <base/selfwidget/rmessagebox.h>
#include <base\util\rutil.h>
#include <commondefines/protocol.h>

#include "../abstractpage.h"
#include "../../customwidget/pageswitchbar.h"
#include "../../customwidget/operationtoolspage.h"

#include "tablemodel/dutyrecordmodel.h"
#include "dialog/dutyrecordeditdialog.h"

#define  DUTY_RECORD_SELET_MAX_INDEX             -1

namespace Related {

	class DutyRecordPage : public AbstractPage
	{
		Q_OBJECT

	public:
		DutyRecordPage(QWidget *parent = nullptr);
		~DutyRecordPage();

		PageType getPageType() const;

		void prepareBringToTop();

		void setTaskId(QString taskId);

	private slots:
		void respToolButtPressed(OperationToolsPage::ButtType type);
		void setPageNum(int page);
		void setFixedPageRowCount(int pageItemCount);

		void processQueryAllDutyRecordResponse(const Datastruct::LoadAllDutyRecordResponse & response);
		void processDutyRecordDeleteResponse(const Datastruct::DutyRecordDeleteResponse & response);

		void slotClickedTable(QModelIndex index);

	private:
		void init();
		void initConnect();

		void deleteDutyRecord(QString id);
		void refreshCurrPage();

	private:
		OperationToolsPage * m_operationToolsPage;				/*!< 操作工具页面 */
		Base::RTableView * m_tableView;							/*!< 数据表格 */
		DutyRecordModel * m_tableModel;							/*!< 数据模型 */
		PageSwitchBar * m_pageSwitch;							/*!< 切换页 */				

		bool m_firstLoadData;									/*!< 第一次加载页面显示 */
		QString m_taskId;										/*!< 任务Id */
		Datastruct::LoadAllDutyRecordResponse m_allDutyRecords;	/*!< 全部值班日志信息 */
		int m_seleteTableRow;									/*!< 选中行数 */
	};

}//namespace Related
