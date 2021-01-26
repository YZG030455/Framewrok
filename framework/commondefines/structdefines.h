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
		ReadOnly = 0x0001,			/*!< ֻ���Բ�ѯ�����ɱ༭ */
		ReadWrite = 0x0002,			/*!< �ɶ�д(��������) */
		DeleteAble = 0x0004,		/*!< ��ɾ�� */
		AllPrivilege = ReadWrite | DeleteAble
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
		int privilege;			/*!< Ȩ�� */
		bool isManager;			/*!< �Ƿ�Ϊ����Ա */
	};

	/*!
	 * @brief  ��������ʵ�����ݽṹ
	 * @details 
	 */
	struct TaskEntityData
	{
		TaskEntityData(){
		}
		QString id;					/*!< ���ݿ�Id */
		QString taskName;		/*!< �������� */
		QString startTime;		/*!< ��ʼʱ�� */
		QString endTime;		/*!< ����ʱ�� */
		QString location;		/*!< ����ص� */

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