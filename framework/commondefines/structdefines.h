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

	/*!
	 * @brief  ��������ʵ�����ݽṹ
	 * @details 
	 */
	struct TaskEntityData
	{
		TaskEntityData():lon(0), lat(0){
		}
		QString id;				/*!< ���ݿ�Id */
		QString taskName;		/*!< �������� */
		QString startTime;		/*!< ��ʼʱ�� */
		QString endTime;		/*!< ����ʱ�� */
		QString location;		/*!< ����ص� */
		double lon;				/*!< ���� */
		double lat;				/*!< γ�� */
		QString description;	/*!< ���� */
		QString detectPlatform;	/*!< ���ƽ̨ */
	};

	/*!
	 * @brief  ����ֵ����־ʵ�����ݽṹ
	 * @details 
	 */
	struct DutyRecordEntityData {
		DutyRecordEntityData() {

		}
		QString id;				/*!< ���ݿ�ID */
		QString taskId;			/*!< ����Id */
		QString createTime;		/*!< ����ʱ�� */
		QString description;	/*!< ���� */
		QString seaCondition;	/*!< ������Ϣ */
	};

	/*!
	 * @brief    ���������¼ʵ�����ݽṹ
	 * @details
	 */
	struct ExperimentRecordEntityData {
		ExperimentRecordEntityData() :lon(0), lat(0){

		}
		QString id;				/*!< ���ݿ�ID */
		QString taskId;			/*!< ����Id */
		QString platformId;		/*!< ƽ̨Id */
		double lon;				/*!< ���� */
		double lat;				/*!< γ�� */
		QString seaCondition;	/*!< ���� */
		QString floatingTime;	/*!< ����ʱ�� */
	};

} //namespace Datastruct 