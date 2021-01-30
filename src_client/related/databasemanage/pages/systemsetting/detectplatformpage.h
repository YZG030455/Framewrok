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

#include <base\selfwidget\iconbutton.h>
#include <base/selfwidget/rmessagebox.h>
#include "../abstractpage.h"
#include "../../customwidget/operationtoolspage.h"

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

		void processQueryAllDetectPlatformResponse(const Datastruct::LoadAllDetectPlatformsResponse & response);
		void processDetectPlatformCreateResponse(const Datastruct::DetectPlatformCreateResponse & response);
		void processDetectPlatformDeleteResponse(const Datastruct::DetectPlatformDeleteResponse & response);
		void processDetectPlatformModifyResponse(const Datastruct::DetectPlatformModifyResponse & response);

		void processQueryAllDetectPlatformSubtypeResponse(const Datastruct::LoadAllDetectPlatformSubtypesResponse & response);
		void processDetectPlatformSubtypeCreateResponse(const Datastruct::DetectPlatformSubtypeCreateResponse & response);
		void processDetectPlatformSubtypeDeleteResponse(const Datastruct::DetectPlatformSubtypeDeleteResponse & response);
		void processDetectPlatformSubtypeModifyResponse(const Datastruct::DetectPlatformSubtypeModifyResponse & response);

	private:
		void init();
		void initConnect();

		void refreshCurrDetectPlatform();
		void insertDetectPlatform(int id, QString name);
		void deleteDetectPlatform(int id);
		void modifyDetectPlatform(Datastruct::DetectPlatformEntityData data);

		void refreshCurrDetectPlatformSubtype(int detectId);
		void insertDetectPlatformSubtype(int detectId, int id, QString name);
		void deleteDetectPlatformSubtype(Datastruct::DetectPlatformSubtypeEntityData data);
		void modifyDetectPlatformSubtype(Datastruct::DetectPlatformSubtypeEntityData data);

	private:
		OperationToolsPage * m_operationToolsPage;				/*!< ��������ҳ�� */
		QComboBox * m_DetectPlatformComboBox;					/*!< ���ƽ̨ */
		QListView * m_DetectPlatformSubtypeListView;			/*!< ���ƽ̨���� */
		bool m_firstLoadData;									/*!< ��һ�μ���ҳ����ʾ */

		Datastruct::LoadAllDetectPlatformsResponse m_detectPlatformsList;
		QMap<int, Datastruct::LoadAllDetectPlatformSubtypesResponse> m_detectPlatformSubtypesResponseMap;


		QMap<QString, int> m_detectPlatformsMap;
		QMap<int, QMap<QString, int>> m_detectPlatformSubtypesMap;
	};

} //namespace Related