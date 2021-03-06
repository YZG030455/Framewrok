/*!
 * @brief     数据协议   
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
	 * @brief 网络连接类型
	 */
	enum ConnectionType {
		Data_Connection,		/*!< 数据连接 */
		File_Connection			/*!< 文件连接 */
	};

	/*!
	 * @brief 用户权限
	 */
	enum UserPrivilege {
		NonePrivilege = 0x0000,		/*!< 无权限 */
		ReadOnly = 0x0001,			/*!< 只可以查询，不可编辑 */
		ReadWrite = 0x0002,			/*!< 可读写(包括更新) */
		DeleteAble = 0x0004,		/*!< 可删除 */
		AllPrivilege = ReadOnly | ReadWrite | DeleteAble		/*!< 全部权限 */
	};

	/*!
	 * @brief 单个用户实体数据结构
	 */
	struct UserEntityData {
		UserEntityData() :id(0), privilege(0), isManager(false){
		}

		int id;					/*!< 数据库ID */
		QString name;			/*!< 用户名 */
		QString password;		/*!< 密码 */
		QString registTime;		/*!< 注册时间 */
		QString lastLoadTime;	/*!< 最后一次登录时间 */
		int privilege;			/*!< 用户具备的权限，@see UserPrivilege */
		bool isManager;			/*!< 是否为管理员,管理员可以修改普通用户的权限，系统中至少存在一个管理员 */
	};

	/*!
	 * @brief 单个侦测平台数据结构
	 */
	struct DetectPlatformEntityData {
		DetectPlatformEntityData() : id(0) {
		}

		int id;							/*!< 唯一标识ID */
		QString name;					/*!< 平台名称 */
	};

	/*!
	 * @brief 单个侦测平台亚型数据结构
	 */
	struct DetectPlatformSubtypeEntityData {
		DetectPlatformSubtypeEntityData() : id(0), detectId(0) {
		}

		int id;							/*!< 唯一标识ID */
		int detectId;					/*!< 侦测平台标识 */
		QString name;					/*!< 平台亚型名称 */
	};

	/*!
	 * @brief  单条任务实体数据结构
	 */
	struct TaskEntityData {
		TaskEntityData() {
		}

		QString id;						/*!< 数据库Id */
		QString taskName;				/*!< 任务名称 */
		QString startTime;				/*!< 起始时间 */
		QString endTime;				/*!< 结束时间 */
		QString location;				/*!< 任务地点 */
		QString lon;					/*!< 经度 */
		QString lat;					/*!< 纬度 */
		QString description;			/*!< 描述 */
	};

	/*!
	 * @brief 单个任务侦测平台表数据结构
	 */
	struct TaskDetectPlatformEntityData {
		TaskDetectPlatformEntityData() : detectId(0), platformPower(0),lastTime(0) {
		}

		QString id;						/*!< 唯一标识 */
		QString taskId;					/*!< 任务标识 */
		int detectId;					/*!< 侦测平台标识 */
		QString name;					/*!< 侦测平台名称 */
		QString sensorType;				/*!< 侦测平台传感器类型 */
		int platformPower;				/*!< 平台动力 */
		QString startTime;				/*!< 开始任务时间 */
		QString endTime;				/*!< 结束任务时间 */
		int lastTime;					/*!< 时长 */
	};

	/*!
	 * @brief 单条任务试验图片资源实体数据结构
	 */
	struct TaskImageEntityData{
		TaskImageEntityData():imageSize(0), recvSize(0) {
		}

		QString id ;					/*!< 唯一标识 */
		QString taskId;					/*!< 任务标识 */
		QString realName;				/*!< 原始图片文件名 */
		QString suffix;					/*!< 图片类型 */
		QString uploadTime;				/*!< 上传时间 */
		qint64 imageSize;				/*!< 图片大小 */
		QString md5;					/*!< 文件MD5值 */
		QString savePath;				/*!< 文件保存路径 */
		qint64 recvSize;					/*!< 文件接收大小 */
		QString description;			/*!< 图片描述 */
	};

	/*!
	 * @brief 单条任务平台原始XML文件信息实体数据结构
	 */
	struct TaskPlatformOriginalXmlEntityData {
		TaskPlatformOriginalXmlEntityData() :fileSize(0), recvSize(0) {
		}

		QString id;						/*!< 唯一标识 */
		QString taskId;					/*!< 任务标识 */
		QString detectPlatformId;		/*!< 平台Id */
		QString realName;				/*!< 原始文件名 */
		qint64 fileSize;				/*!< 文件大小 */
		QString startTime;				/*!< 开始时间 */
		QString endTime;				/*!< 结束时间 */
		QString md5;					/*!< 文件MD5值 */
		QString savePath;				/*!< 文件保存路径 */
		qint64 recvSize;				/*!< 文件接收大小 */
	};

	/*!
	 * @brief 单条任务平台原始Data文件信息实体数据结构
	 */
	struct TaskPlatformOriginalDataEntityData {
		TaskPlatformOriginalDataEntityData() :fileSize(0), startFrameIndex(0), endFrameIndex(0), recvSize(0){
		}

		QString id;						/*!< 唯一标识 */
		QString taskId;					/*!< 任务标识 */
		QString detectPlatformId;		/*!< 平台Id */
		QString realName;				/*!< 原始文件名 */
		qint64 fileSize;				/*!< 文件大小 */
		qint64 startFrameIndex;			/*!< 开始帧序号 */
		qint64 endFrameIndex;			/*!< 结束帧序号 */
		QString startTime;				/*!< 开始时间 */
		QString endTime;				/*!< 结束时间 */
		QString md5;					/*!< 文件MD5值 */
		QString savePath;				/*!< 文件保存路径 */
		qint64 recvSize;				/*!< 文件接收大小 */
	};

	/*!
	 * @brief  单条值班日志实体数据结构
	 */
	struct DutyRecordEntityData {
		DutyRecordEntityData():wind(0), windSpeed(0),waveHigh(0), oceanCurrents(0){
		}

		QString id;						/*!< 唯一标识 */
		QString taskId;					/*!< 任务标识 */
		QString createTime;				/*!< 创建时间 */
		QString description;			/*!< 描述信息 */
		QString seaCondition;			/*!< 海况 */
		double wind;					/*!< 风向 */
		double windSpeed;				/*!< 风速 */
		double waveHigh;				/*!< 浪高 */
		double oceanCurrents;			/*!< 洋流 */
	};

	/*!
	 * @brief    单条试验记录实体数据结构
	 */
	struct ExperimentRecordEntityData {
		ExperimentRecordEntityData() :lon(0), lat(0), setHeadingDegree(0),actualHeadingDegree(0), acousticState(0), 
			targetNum(0), underwaterTargetNum(0),maxDepth(0), profileIndex(0), profileLength(0), profileDistance(0){
		}

		QString id;						/*!< 唯一标识 */
		QString taskId;					/*!< 任务标识 */
		QString platformId;				/*!< 平台标识 */
		QString floatingTime;			/*!< 上浮时间 */
		double lon;						/*!< 上浮经度 */
		double lat;						/*!< 上浮纬度 */
		double setHeadingDegree;		/*!< 设置航向角 */
		double actualHeadingDegree;		/*!< 实际航向角 */
		int acousticState;				/*!< 声学系统状态 */
		int targetNum;					/*!< 目标总数 */
		int underwaterTargetNum;		/*!< 水下目标数 */
		QString underwaterTargetInfo;	/*!< 水下目标信息 */
		double maxDepth;				/*!< 剖面最大深度 */
		int profileIndex;				/*!< 剖面序号 */
		double profileLength;			/*!< 剖面时长 */
		double profileDistance;			/*!< 剖面移动距离 */
	};

	/*!
	 * @brief 目标实体数据
	 */
	struct  TargetEntityData {
		TargetEntityData() :type(0), tonnage(0), lon(0), lat(0), speed(0), axlesNumber(0){

		}

		QString id;					/*!< 唯一标识 */
		QString name;				/*!< 目标名称 */
		QString createTime;			/*!< 创建时间 */
		int type;					/*!< 类型 */
		double tonnage;				/*!< 吨位 */
		double lon;					/*!< 经度 */
		double lat;					/*!< 纬度 */
		double speed;				/*!< 航行速度 */
		int  axlesNumber;			/*!< 轴数 */
	};

	/*!
	 * @brief 目标音频实体数据
	 */
	struct  TargetWavEntityData {
		TargetWavEntityData() :tonnage(0), lon(0), lat(0), speed(0), axlesNumber(0), datalength(0),
			type(0){
		}

		QString  id;				/*!< 索引 */
		QString targetName;			/*!< 目标名称 */
		QString edttime;			/*!< 录取时间 */
		double tonnage;				/*!< 吨位 */
		double lon;					/*!< 经度 */
		double lat;					/*!< 纬度 */
		double speed;				/*!< 航行速度 */
		int  axlesNumber;			/*!< 轴数 */
		int datalength;				/*!< 数据时长 */
		int type;					/*!< 类型 */
	};

	/*!
	 * @brief AIS实体数据
	 */
	struct AisEntityData{
		AisEntityData():mmsi(0), time(0), lon(0), lat(0), course(0), truehead(0),
			shipType(0), shipImo(0), navStatus(0),speed (0), length(0), width(0){
		}

		QString id;					/*!< 唯一标识 */
		QString targetId;			/*!< 目标标识 */
		int mmsi;					/*!< 船舶MMSI */
		int time;					/*!< 实时信号时间 */
		double lon;					/*!< 经度 */
		double lat;					/*!< 纬度 */
		double course;				/*!< 航迹向 */
		int  truehead;				/*!< 航首向 */
		QString name;				/*!< 船名 */
		int shipType;				/*!< 船舶以及货物类型 */
		int shipImo;				/*!< 船舶IMO */
		int navStatus;				/*!< 航行状态 */
		double speed;				/*!< 航行速度 */
		QString eta;				/*!< 预计到港时间 */
		QString dest;				/*!< 目的港 */
		double length;				/*!< 船长 */
		double width;				/*!< 船宽 */
		QString callsign;			/*!< 呼号 */
		QString flag;				/*!< 船旗 */
		QString buildDate;			/*!< 建造时间 */
		QString port;				/*!< 船籍港 */
	};

} //namespace Datastruct 