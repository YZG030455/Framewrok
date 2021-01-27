/*!
 * @brief     �����¼����
 * @author    yzg
 * @version   1.0
 * @date      2021.01.23 11:06:46
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

#include "../abstractpage.h"
#include "../customwidget/pageswitchbar.h"
#include "customwidget/operationtoolspage.h"
#include "tablemodel/trialsheetmodel.h"

namespace Related {

	class TrialSheetWidget : public AbstractPage
	{
		Q_OBJECT

	public:
		TrialSheetWidget(QWidget *parent  = nullptr);
		~TrialSheetWidget();

		PageType getPageType() const;

		void prepareBringToTop();

		void setTaskId(QString taskId);

	private slots:
		void respToolButtPressed(OperationToolsPage::ButtType type);
		void processExperimentRecordCreateResponse(const Datastruct::ExperimentRecordCreateResponse & response);
		void processQueryAllExperimentRecordResponse(const Datastruct::LoadAllExperimentRecordsResponse & response);
		void processExperimentRecordDeleteResponse(const Datastruct::ExperimentRecordDeleteResponse & response);

	private:
		void init();
		void initConnent();

		void insertExperimentRecord();
		void refreshCurrPage();

	private:
		OperationToolsPage * m_operationToolsPage;			/*!< ��������ҳ�� */
		Base::RTableView * m_tableView;						/*!< ���ݱ�� */	
		TrialSheetModel * m_tableModel;						/*!< ����ģ�� */
		PageSwitchBar * m_pageSwitch;						/*!< �л�ҳ */

		bool m_firstLoadData;								/*!< ��һ�μ���ҳ����ʾ */
		QString m_taskId;									/*!< ����Id */
	};

} // namespace Related 