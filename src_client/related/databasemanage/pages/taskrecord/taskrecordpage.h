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

#include "logbookpage.h"
#include "trialsheetwidget.h"
#include "taskreportswidget.h"

namespace Related {

	class TaskRecordPage : public AbstractPage
	{
		Q_OBJECT

	public:
		TaskRecordPage(QWidget *parent = nullptr);
		~TaskRecordPage();

		PageType getPageType() const;

	private:
		void init();

	private:
		Base::RTabWidget * m_tabWidget;

		LogbookPage *m_logbookPage;						/*!< ֵ����־���� */
		TrialSheetWidget * m_trialSheetWidget;			/*!< �����¼���� */
		TaskReportsWidget * m_taskReportsWidget;		/*!< ���񱨸���� */
	}; 

} //namespace Related 