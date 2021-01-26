/*!
 *  @brief    ��������ҳ��
 *  @details  ��ҳ���ṩ ���ӡ�ɾ�����޸ġ�ˢ��
 *  @author    yzg
 *  @version   1.0
 *  @date      2021.1.14
 *  @warning
 *  @copyright NanJing RenGu.
 *  @note
 */
#pragma once

#include <QObject>
#include <QWidget>
#include <qlabel.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMap>

#include <base\selfwidget\iconbutton.h>
#include <base\macros.h>

namespace Related {

	class OperationToolsPage : public QWidget
	{
		Q_OBJECT

	public:
		OperationToolsPage(QWidget *parent = nullptr);
		~OperationToolsPage();

		enum ButtType {
			Butt_Add = 0x0001,		/*!< ��� */
			Butt_Delete = 0x0002,	/*!< ɾ�� */
			Butt_Edit = 0x0004,		/*!< �޸� */
			Butt_Refresh = 0x0008	/*!< ˢ�� */
		};
		Q_DECLARE_FLAGS(ButtTypes, ButtType)
		Q_DECLARE_FRIEND_FLAGS(ButtTypes)

		/*! 
		 * @brief ���ö����ť����
		 * @param butts �����ť��Ӧ��ö��ֵ����
		 * @param visible true:��ť��ʾ��false:��ť����
		 */
		void setButtVisible(ButtTypes butts,bool visible = false);

	signals:
		void buttPressed(OperationToolsPage::ButtType type);

	private slots:
		void respButtCliecked();

	private:
		void  init();

	private:
		Base::RIconButton * m_addButton;
		Base::RIconButton * m_delButton;
		Base::RIconButton * m_editButton;
		Base::RIconButton * m_refreshButton;

		QMap<ButtType, Base::RIconButton *> m_buttMap;
	};

}//namespace Related 