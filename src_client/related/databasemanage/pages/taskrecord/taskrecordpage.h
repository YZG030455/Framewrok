/*!
 * @brief     �����¼ҳ��
 * @details   �ṩֵ����¼�������¼��ҳ��
 * @author    wey
 * @version   1.0
 * @date      2021.01.20 09:16:07
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
 #pragma once

#include <QWidget>
#include <QStackedWidget>

#include <base\selfwidget\rtabwidget.h>

#include "../abstractpage.h"

#include "dutyrecordpage.h"
#include "experimentrecordpage.h"
#include "taskreportpage.h"

namespace Related {

	class TaskRecordPage : public AbstractPage
	{
		Q_OBJECT

	public:
		TaskRecordPage(QWidget *parent = nullptr);
		~TaskRecordPage();

		PageType getPageType() const;
		
		void prepareBringToTop();

		void setTaskId(QString taskId);

	private:
		void init();

	private:
		Base::RTabWidget * m_tabWidget;

		DutyRecordPage * m_logbookPage;					/*!< ֵ����־���� */
		ExperimentRecordPage * m_trialSheetWidget;		/*!< �����¼���� */
		TaskReportPage * m_taskReportsPage;				/*!< ���񱨸���� */
	}; 

} //namespace Related 