/*!
 * @brief     ����Э��   
 * @author    wey
 * @version   1.0
 * @date      2021.01.23 15:17:10
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
 #pragma once

#include <QObject>
#include <QString>
#include <QDateTime>

namespace Datastruct {

	enum UserPrivilege {
		NonePrivilege = 0x0000,		/*!< ��Ȩ�� */
		ReadOnly = 0x0001,			/*!< ֻ���Բ�ѯ�����ɱ༭ */
		ReadWrite = 0x0002,			/*!< �ɶ�д(��������) */
		DeleteAble = 0x0004,		/*!< ��ɾ�� */
		AllPrivilege = ReadOnly | ReadWrite | DeleteAble		/*!< ȫ��Ȩ�� */
	};

	/*!
	 * @brief �����û�ʵ�����ݽṹ
	 * @details 
	 */
	struct UserEntityData {
		UserEntityData() :id(0), isManager(false){}

		int id;					/*!< ���ݿ�ID */
		QString name;			/*!< �û��� */
		QString password;		/*!< ���� */
		QString registTime;		/*!< ע��ʱ�� */
		QString lastLoadTime;	/*!< ���һ�ε�¼ʱ�� */
		int privilege;			/*!< �û��߱���Ȩ�ޣ�@see UserPrivilege */
		bool isManager;			/*!< �Ƿ�Ϊ����Ա,����Ա�����޸���ͨ�û���Ȩ�ޣ�ϵͳ�����ٴ���һ������Ա */
	};

} //namespace Datastruct 