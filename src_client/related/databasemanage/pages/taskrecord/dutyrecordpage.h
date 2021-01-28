/*!
 * @brief     ֵ����־��  
 * @details
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
#include <base\util\rutil.h>
#include <commondefines/protocol.h>

#include "../abstractpage.h"
#include "../customwidget/pageswitchbar.h"

#include "customwidget/operationtoolspage.h"
#include "tablemodel/dutyrecordmodel.h"

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
		void processDutyRecordCreateResponse(const Datastruct::DutyRecordCreateResponse & response);
		void processQueryAllDutyRecordResponse(const Datastruct::LoadAllDutyRecordResponse & response);
		void processDutyRecordDeleteResponse(const Datastruct::DutyRecordDeleteResponse & response);
		void processDutyRecordModifyResponse(const Datastruct::DutyRecordModifyResponse & response);

		void slotClickedTable(QModelIndex index);

	private:
		void init();
		void initConnect();
		void insertDutyRecord();
		void deleteDutyRecord(QString id);
		void modifyDutyRecord(Datastruct::DutyRecordEntityData info);
		void refreshCurrPage();

	private:
		OperationToolsPage * m_operationToolsPage;				/*!< ��������ҳ�� */
		Base::RTableView * m_tableView;							/*!< ���ݱ�� */
		DutyRecordModel * m_tableModel;							/*!< ����ģ�� */
		PageSwitchBar * m_pageSwitch;							/*!< �л�ҳ */				

		bool m_firstLoadData;									/*!< ��һ�μ���ҳ����ʾ */
		QString m_taskId;										/*!< ����Id */
		Datastruct::LoadAllDutyRecordResponse m_allDutyRecords;	/*!< ȫ��ֵ����־��Ϣ */
		int m_seleteTableRow;									/*!< ѡ������ */
	};

}//namespace Related
