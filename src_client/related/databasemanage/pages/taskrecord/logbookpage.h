/*!
 * @brief     ֵ����־��  
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

#include <base\selfwidget\tablemode\rtableview.h>
#include <base\selfwidget\iconbutton.h>
#include <base\util\rutil.h>
#include <commondefines/protocol.h>

#include "../customwidget/pageswitchbar.h"

#include "customwidget/operationtoolspage.h"
#include "tablemodel/logbookmodel.h"

namespace Related {

	class LogbookPage : public QWidget
	{
		Q_OBJECT

	public:
		LogbookPage(QWidget *parent = nullptr);
		~LogbookPage();

	private slots:
		void respToolButtPressed(OperationToolsPage::ButtType type);
		void processDutyRecordCreateResponse(const Datastruct::DutyRecordCreateResponse & response);
		void processQueryAllDutyRecordResponse(const Datastruct::LoadAllDutyRecordResponse & response);
		void processDutyRecordDeleteResponse(const Datastruct::DutyRecordDeleteResponse & response);

	private:
		void init();
		void initConnect();
		void insertDutyRecord();

		void refreshCurrPage();

	private:
		OperationToolsPage *m_operationToolsPage;			/*!< ��������ҳ�� */
		Base::RTableView * m_tableView;						/*!< ���ݱ�� */
		LogbookModel * m_tableModel;						/*!< ����ģ�� */
		PageSwitchBar * m_pageSwitch;						/*!< �л�ҳ */				

		QString m_taskId;
	};

}//namespace Related
