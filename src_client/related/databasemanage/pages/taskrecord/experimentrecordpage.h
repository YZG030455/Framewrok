/*!
 * @brief     �����¼����
 * @details
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
#include "../../customwidget/pageswitchbar.h"
#include "../../customwidget/operationtoolspage.h"
#include "tablemodel/experimentrecordmodel.h"

namespace Related {

	class ExperimentRecordPage : public AbstractPage
	{
		Q_OBJECT

	public:
		ExperimentRecordPage(QWidget *parent  = nullptr);
		~ExperimentRecordPage();

		PageType getPageType() const;

		void prepareBringToTop();

		void setTaskId(QString taskId);

	private slots:
		void respToolButtPressed(OperationToolsPage::ButtType type);
		void processExperimentRecordCreateResponse(const Datastruct::ExperimentRecordCreateResponse & response);
		void processQueryAllExperimentRecordResponse(const Datastruct::LoadAllExperimentRecordsResponse & response);
		void processExperimentRecordDeleteResponse(const Datastruct::ExperimentRecordDeleteResponse & response);
		void processExperimentRecordModifyResponse(const Datastruct::ExperimentRecordModifyResponse & response);
		void slotClickedTable(QModelIndex index);

	private:
		void init();
		void initConnent();

		void insertExperimentRecord();
		void deleteExperimentRecord(QString id);
		void modifyExperimentRecord(Datastruct::ExperimentRecordEntityData data);
		void refreshCurrPage();

	private:
		OperationToolsPage * m_operationToolsPage;			/*!< ��������ҳ�� */
		Base::RTableView * m_tableView;						/*!< ���ݱ��� */	
		ExperimentRecordModel * m_tableModel;				/*!< ����ģ�� */
		PageSwitchBar * m_pageSwitch;						/*!< �л�ҳ */

		bool m_firstLoadData;													/*!< ��һ�μ���ҳ����ʾ */
		QString m_taskId;														/*!< ����Id */
		Datastruct::LoadAllExperimentRecordsResponse m_allExperimentRecords;    /*!< ȫ��������Ϣ */
		int m_seleteTableRow;													/*!< ѡ������ */
	};

} // namespace Related 