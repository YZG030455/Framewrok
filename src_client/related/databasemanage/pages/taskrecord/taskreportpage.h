/*!
 * @brief     ���񱨸����
 * @details 
 * @author    yzg
 * @version   1.0
 * @date      2021.01.27 11:02:25
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedWidget>

#include <base\selfwidget\iconbutton.h>
#include <base/selfwidget/rmessagebox.h>
#include <base\util\rutil.h>
#include <commondefines/protocol.h>

#include "../abstractpage.h"
#include "taskreporteditpage.h"
#include "taskreportpreviewpage.h"

namespace Related {

	class TaskReportPage : public AbstractPage
	{
		Q_OBJECT

	public:
		TaskReportPage(QWidget *parent = nullptr);
		~TaskReportPage();

		PageType getPageType() const;

		void prepareBringToTop();

		void setTaskId(QString taskId);

	private slots:
		void slotPreviewReport();
		void slotQuiePreviewReport();
		void slotSaveReport();

	private:
		void  init();
		void  initConnect();
	private:
		QStackedWidget * m_stackedWidget;

		Base::RIconButton * m_previewButt;
		Base::RIconButton * m_quitButt;
		Base::RIconButton * m_saveButt;

		TaskReportEditPage  * m_taskReportEditPage;				/*!< ���鱨��༭���� */
		TaskReportPreviewPage * m_taskReportPreviewPage;		/*!< ���鱨��Ԥ������ */

		bool m_firstLoadData;			/*!< ��һ�μ���ҳ����ʾ */
		QString m_taskId;				/*!< ����Id */
	};

}//namespace Related 