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

	/*!
	 * @brief ������������
	 */
	enum ConnectionType {
		Data_Connection,		/*!< �������� */
		File_Connection			/*!< �ļ����� */
	};

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
		QString taskName;			/*!< �������� */
		QString startTime;			/*!< ��ʼʱ�� */
		QString endTime;			/*!< ����ʱ�� */
		QString location;			/*!< ����ص� */
		QString lon;				/*!< ���� */
		QString lat;				/*!< γ�� */
		QString description;		/*!< ���� */
	};

	/*!
	 * @brief ������������ͼƬ��Դʵ�����ݽṹ
	 * @details 
	 */
	struct TaskImageEntityData{

		QString id ;				/*!< Ψһ��ʶ */
		QString taskId;				/*!< �����ʶ */
		QString realName;			/*!< ԭʼͼƬ�ļ��� */
		QString suffix;				/*!< ͼƬ���� */
		QString uploadTime;			/*!< �ϴ�ʱ�� */
		double imageSize;			/*!< ͼƬ��С */
		QString description;			/*!< ͼƬ���� */
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
		DetectPlatformSubtypeEntityData() : id(0), detectId(0) {}

		int id;					/*!< Ψһ��ʶID */
		int detectId;			/*!< ���ƽ̨��ʶ */
		QString name;			/*!< ƽ̨�������� */
	};

	/*!
	 * @brief �����������ƽ̨�����ݽṹ
	 * @details
	 */
	struct TaskDetectPlatformEntityData {
		TaskDetectPlatformEntityData() : detectId(0), platformPower(0),
			lastTime(0) {}

		QString id;					/*!< Ψһ��ʶ */
		QString taskId;				/*!< �����ʶ */
		int detectId;				/*!< ���ƽ̨��ʶ */
		QString name;				/*!< ���ƽ̨���� */
		QString sensorType;			/*!< ���ƽ̨���������� */
		int platformPower;			/*!< ƽ̨���� */
		QString startTime;			/*!< ��ʼ����ʱ�� */
		QString endTime;			/*!< ��������ʱ�� */
		int lastTime;				/*!< ʱ�� */
	};

	/*!
	 * @brief Ŀ��ʵ������
	 */
	struct  TargetEntityData {
		TargetEntityData() :type(0){

		}
		QString id;					/*!< Ψһ��ʶ */
		QString name;				/*!< Ŀ������ */
		QString createTime;			/*!< ����ʱ�� */
		int type;					/*!< ���� */
		double tonnage;				/*!< ��λ */
		double lon;					/*!< ���� */
		double lat;					/*!< γ�� */
		double speed;				/*!< �����ٶ� */
		int  axlesNumber;			/*!< ���� */
	};

	/*!
 * @brief Ŀ����Ƶʵ������
 */
	struct  TargetWavEntityData {
		QString  id;				/*!< ���� */
		QString targetName;			/*!< Ŀ������ */
		QString edttime;			/*!< ¼ȡʱ�� */
		double tonnage;				/*!< ��λ */
		double lon;					/*!< ���� */
		double lat;					/*!< γ�� */
		double speed;				/*!< �����ٶ� */
		int  axlesNumber;			/*!< ���� */
		int datalength;				/*!< ����ʱ�� */
		int type;					/*!< ���� */
	};


	/*!
	 * @brief AISʵ������
	 */
	struct AisEntityData{
		AisEntityData():mmsi(0), time(0), lon(0), lat(0), course(0), truehead(0),
			shipType(0), shipImo(0), navStatus(0),speed (0), length(0), width(0){
		}

		QString id;					/*!< Ψһ��ʶ */
		QString targetId;			/*!< Ŀ���ʶ */
		int mmsi;					/*!< ����MMSI */
		int time;					/*!< ʵʱ�ź�ʱ�� */
		double lon;					/*!< ���� */
		double lat;					/*!< γ�� */
		double course;				/*!< ������ */
		int  truehead;				/*!< ������ */
		QString name;				/*!< ���� */
		int shipType;				/*!< �����Լ��������� */
		int shipImo;				/*!< ����IMO */
		int navStatus;				/*!< ����״̬ */
		double speed;				/*!< �����ٶ� */
		QString eta;				/*!< Ԥ�Ƶ���ʱ�� */
		QString dest;				/*!< Ŀ�ĸ� */
		double length;				/*!< ���� */
		double width;				/*!< ���� */
		QString callsign;			/*!< ���� */
		QString flag;				/*!< ���� */
		QString buildDate;			/*!< ����ʱ�� */
		QString port;				/*!< ������ */
	};

} //namespace Datastruct 