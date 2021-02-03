/*!
 * @brief     ���ƽ̨����
 * @details   
 * @author    yzg
 * @version   1.0
 * @date      2021.01.29 18:17:58
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
 #pragma once

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QListView>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QMap>
#include <QEvent>
#include <QMenu>
#include <QAction>

#include <base\selfwidget\iconbutton.h>
#include <base/selfwidget/rmessagebox.h>
#include "../abstractpage.h"
#include "../../customwidget/operationtoolspage.h"

#include "dialog/detectplatformeditdialog.h"

#define  TABLEMODEL_MAX_INDEX             -1

namespace Related {

	class DetectPlatformPage : public AbstractPage
	{
		Q_OBJECT

	public:
		DetectPlatformPage(QWidget *parent = nullptr);
		~DetectPlatformPage();

		PageType getPageType() const;

		void prepareBringToTop();

	private slots:
		void respToolButtPressed(OperationToolsPage::ButtType type);
		void slotActivated(const QString &text);
		void slotCreateNewDetectPlatformSubtypeTriggered();
		void slotDetectPlatformSubtypeClicked(QModelIndex index);
		void slotDeleteDetectPlatformSubtypeTriggered();

		void processQueryAllDetectPlatformResponse(const Datastruct::LoadAllDetectPlatformsResponse & response);
		void processDetectPlatformDeleteResponse(const Datastruct::DetectPlatformDeleteResponse & response);

		void processQueryAllDetectPlatformSubtypeResponse(const Datastruct::LoadAllDetectPlatformSubtypesResponse & response);
		void processDetectPlatformSubtypeDeleteResponse(const Datastruct::DetectPlatformSubtypeDeleteResponse & response);

	protected:
		void contextMenuEvent(QContextMenuEvent *event);

	private:
		void init();
		void initConnect();

		void refreshCurrDetectPlatform();
		void deleteDetectPlatform(int id);

		void refreshCurrDetectPlatformSubtype(int detectId);
		void deleteDetectPlatformSubtype(QString name);

	private:
		OperationToolsPage * m_operationToolsPage;				/*!< ��������ҳ�� */
		QComboBox * m_DetectPlatformComboBox;					/*!< ���ƽ̨ */
		QListView * m_DetectPlatformSubtypeListView;			/*!< ���ƽ̨���� */
		QStandardItemModel * m_listModel;
		bool m_firstLoadData;									/*!< ��һ�μ���ҳ����ʾ */

		Datastruct::LoadAllDetectPlatformsResponse m_detectPlatformsList;

		QMap<int, Datastruct::LoadAllDetectPlatformSubtypesResponse> m_detectPlatformSubtypesResponseMap;

		QMap<QString, int>  m_detectPlatformsMap;

		QModelIndex m_selectedModelIndex;
		int m_selectedIndex;	
		bool m_selectedModel;
	};

} //namespace Related