/*!
 * @brief     ������������ҳ��   
 * @author    wey
 * @version   1.0
 * @date      2021.01.16 17:17:01
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
#pragma once

#include <QWidget>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

#include <base/selfwidget/tablemode/rtableview.h>
#include <base/selfwidget/rmessagebox.h>

#include "../abstractpage.h"
#include "../../customwidget/pageswitchbar.h"
#include "../../customwidget/operationtoolspage.h"

#include "tablemodel/detectplatformsubtypemodel.h"

namespace Related {

	class OtherSettingPage : public AbstractPage
	{
		Q_OBJECT

	public:
		OtherSettingPage(QWidget *parent = nullptr);
		~OtherSettingPage();

		PageType getPageType() const;

	private slots:
		void processQueryAllDetectPlatformResponse(Datastruct::LoadAllDetectPlatformsResponse response);
		void processQueryAllDetectPlatformSubtypeResponse(Datastruct::LoadAllDetectPlatformSubtypesResponse response);
	private:
		void init();
		void initConnect();

		void refreshCurrDetectPlatform();
		void refreshCurrDetectPlatformSubtype(int detectId);

	private:
		OperationToolsPage * m_operationToolsPage;				/*!< ��������ҳ�� */
		QComboBox * m_comboBox;
		Base::RTableView * m_detectPlatformSubtypeTableView;
		PageSwitchBar * m_pageSwitch;								/*!< �л�ҳ */
		DetectPlatformSubtypeModel * m_detectPlatformSubtypeTableModel;

	};

} //namespace Related 