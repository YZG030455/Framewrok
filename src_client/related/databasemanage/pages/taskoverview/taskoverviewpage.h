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
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QDateTime>
#include <QListView>

#include <base/selfwidget/iconbutton.h>
#include <base/util/rutil.h>
#include <commondefines/protocol.h>

#include "../../net/signaldispatch.h"
#include "../../net/datanetconnector.h"

#include "../abstractpage.h"
#include "../systemmainpage/overviewitem.h "
#include "../../customwidget/customwidgetcontainer.h"

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
		void prepareBringToTop();

		void setTaskId(QString taskId);

	private slots:
		void processTaskSimpleResponse(const Datastruct::TaskSimpleResponse & response);
		void slotSeleteImagesIndex(int index);

	private:
		void init();
		void initConnect();
		void refreshCurrTaskSimple();

	private:
		OverViewItem * m_taskPlatformType;
		OverViewItem * m_platformdataSize;
		OverViewItem * m_advSize;

		TaskBaseInfoPage   * m_taskBaseInfoPage;			/*!< ���������Ϣ */
		TaskResultInfoPage * m_taskResultInfoPage;			/*!< ���ݽ����Ϣ���� */

		bool m_firstLoadData;								/*!< ��һ�μ���ҳ����ʾ */
		QString m_taskId;									/*!< ����Id */
	};

} //namespace Related 