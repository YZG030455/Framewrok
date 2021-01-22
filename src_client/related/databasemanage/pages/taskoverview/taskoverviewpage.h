/*!
 * @brief     �������ҳ��   
 * @author    wey
 * @version   1.0
 * @date      2021.01.20 09:13:41
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
 #pragma once

#include <QWidget>
#include <QDateTimeEdit>
#include <QComboBox>
#include <QtWidgets/QScrollArea>
#include <QScrollArea>

#include <base/selfwidget/iconbutton.h>


#include "systemmainpage/overviewitem.h "
#include "../../customwidget/timerangeedit.h"
#include "../abstractpage.h"
#include "../../3rdLibrary/qcustomplot.h"

#include "taskbaseinfopage.h"
#include "taskresultinfopage.h"

namespace Related {

	class TaskOverViewPage : public AbstractPage
	{
		Q_OBJECT

	public:
		TaskOverViewPage(QWidget *parent = nullptr);
		~TaskOverViewPage();

		PageType getPageType() const;

		void  updateTaskInfo();

	private:
		void init();

	private:
		OverViewItem * m_taskPlatformType;
		OverViewItem * m_platformdataSize;
		OverViewItem * m_advSize;

		TaskBaseInfoPage   * m_taskBaseInfoPage;			/*!< ���������Ϣ */
		TaskResultInfoPage * m_taskResultInfoPage;			/*!< ���ݽ����Ϣ���� */
	};

} //namespace Related 