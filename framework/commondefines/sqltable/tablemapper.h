/*!
 * @brief     ���ݿ���ֶ�ӳ��
 * @details   ����������ݿ���Լ����ֶ���,�����ڷ������ݿ��дsqlʱ�����ٶ��ֶε�Ӳ����
 * @author    wey
 * @version   1.0
 * @date      2021.01.23 14:08:34
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
 #pragma once

#include <QObject>
#include <QString>

namespace Table {

	struct AbstractTable {
		AbstractTable(QString tname):table(tname) {}
		QString table;
	};

	/*!
	 * @brief �û���Ϣ��
	 */
	struct UserEntity : public AbstractTable {
		UserEntity() :AbstractTable("user_entity") {}

		QString id = "id";
		QString userName = "user_name";
		QString userPassword = "user_password";
		QString regitstTime = "regist_time";
		QString privilege = "privilege";
		QString superManage = "super_manage";
	};


}	//namespace Table
