/*!
 * @brief     �û�����������ģ��
 * @author    yzg
 * @version   1.0
 * @date      2021.01.13 13:45:13
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
#pragma once

#include <QObject>

#include <commondefines\protocol.h>
#include <base\selfwidget\tablemode\rtablemodel.h>
#include "../../../datastruct.h"

namespace Related {

	class UserManageModel : public Base::RTableModel
	{
		Q_OBJECT

	public:
		UserManageModel(QObject *parent = nullptr);
		~UserManageModel();

		int datasSize() const;

		void updateData(const QList<Datastruct::UserEntityData> & dlist);

		/*! 
		 * @brief ��ȡָ�������������ݿ��е�����
		 * @param row ����к�
		 * @return ���ݿ�����
		 */
		int getRecordDatabaseIndex(int row);

		/*!
		 * @brief ��ȡָ�����û�Ȩ��
		 * @param row ����к�
		 * @return �û�Ȩ��
		 */
		int getUserPrivilege(int row);

		/*!
		 * @brief ��ȡָ�����Ƿ�Ϊ����Ա��ɫ
		 * @param row ����к�
		 * @return true:����Ա��ɫ��false:�ǹ���Ա��ɫ
		 */
		bool isUserManage(int row);

	protected:
		QVariant displayData(int rowIndex, int dataIndex, int columnId) const;

	private:
		QList<Datastruct::UserEntityData> m_dataList;

	};

}//namespace Related 
