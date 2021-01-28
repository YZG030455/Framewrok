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
	struct TaskEntityData {
		TaskEntityData() {
		}
		QString id;				/*!< ���ݿ�Id */
		QString taskName;		/*!< �������� */
		QString startTime;		/*!< ��ʼʱ�� */
		QString endTime;		/*!< ����ʱ�� */
		QString location;		/*!< ����ص� */
		QString lon;			/*!< ���� */
		QString lat;			/*!< γ�� */
		QString description;	/*!< ���� */
	};

	/*!
	 * @brief �������ƽ̨���ݽṹ
	 * @details
	 */
	struct DetectPlatformEntityData {
		DetectPlatformEntityData() : id(0) {}

		int id;					/*!< Ψһ��ʶID */
		QString name;			/*!< ƽ̨���� */
	};

	/*!
	 * @brief �������ƽ̨�������ݽṹ
	 * @details
	 */
	struct DetectPlatformSubtypeEntityData {
		DetectPlatformSubtypeEntityData() : id(0), detectId(0){}

		int id;					/*!< Ψһ��ʶID */
		int detectId;			/*!< ���ƽ̨��ʶ */
		QString name;			/*!< ƽ̨�������� */
	};

	/*!
	 * @brief �����������ƽ̨�����ݽṹ
	 * @details
	 */
	struct TaskDetectPlatformEntityData {
		TaskDetectPlatformEntityData() : detectId(0), platformPower (0),
			lastTime(0){}

		QString id;					/*!< Ψһ��ʶ */
		QString taskId;				/*!< �����ʶ */
		int detectId;			/*!< ���ƽ̨��ʶ */
		QString name;				/*!< ���ƽ̨���� */
		QString sensorType;			/*!< ���ƽ̨���������� */
		int platformPower;			/*!< ƽ̨���� */
		QString startTime;			/*!< ��ʼ����ʱ�� */
		QString endTime;			/*!< ��������ʱ�� */
		int lastTime;				/*!< ʱ�� */
	};

	/*!
	 * @brief  ����ֵ����־ʵ�����ݽṹ
	 * @details 
	 */
	struct DutyRecordEntityData {
		DutyRecordEntityData():wind(0), windSpeed(0),
			waveHigh(0), oceanCurrents(0){

		}
		QString id;						/*!< Ψһ��ʶ */
		QString taskId;					/*!< �����ʶ */
		QString createTime;				/*!< ����ʱ�� */
		QString description;			/*!< ������Ϣ */
		QString seaCondition;			/*!< ���� */
		double wind;					/*!< ���� */
		double windSpeed;				/*!< ���� */
		double waveHigh;				/*!< �˸� */
		double oceanCurrents;			/*!< ���� */
	};

	/*!
	 * @brief    ���������¼ʵ�����ݽṹ
	 * @details
	 */
	struct ExperimentRecordEntityData {
		ExperimentRecordEntityData() :lon(0), lat(0), setHeadingDegree(0),
			actualHeadingDegree(0), acousticState(0), targetNum(0), underwaterTargetNum(0),
			maxDepth(0), profileIndex(0), profileLength(0), profileDistance(0){

		}
		QString id;						/*!< Ψһ��ʶ */
		QString taskId;					/*!< �����ʶ */
		QString platformId;				/*!< ƽ̨��ʶ */
		QString floatingTime;			/*!< �ϸ�ʱ�� */
		double lon;						/*!< �ϸ����� */
		double lat;						/*!< �ϸ�γ�� */
		double setHeadingDegree;		/*!< ���ú���� */
		double actualHeadingDegree;		/*!< ʵ�ʺ���� */
		int acousticState;				/*!< ��ѧϵͳ״̬ */
		int targetNum;					/*!< Ŀ������ */
		int underwaterTargetNum;		/*!< ˮ��Ŀ���� */
		QString underwaterTargetInfo;	/*!< ˮ��Ŀ����Ϣ */
		double maxDepth;				/*!< ���������� */
		int profileIndex;				/*!< ������� */
		double profileLength;			/*!< ����ʱ�� */
		double profileDistance;			/*!< �����ƶ����� */
	};

} //namespace Datastruct 