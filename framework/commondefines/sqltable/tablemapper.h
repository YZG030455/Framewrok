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
		QString lastLoadTime = "last_load_time";
		QString privilege = "privilege";
		QString superManage = "super_manager";
	};

	/*!
	 * @brief ������Ϣ��
	*/
	struct TaskEntity : public AbstractTable {
		TaskEntity() :AbstractTable("task_entity") {}

		QString id = "id";
		QString name = "name";
		QString startTime = "start_time";
		QString endTime = "end_time";
		QString location = "location";
		QString lon = "lon";
		QString lat = "lat";
		QString description = "description";
	};

	/*!
	 * @brief ���ƽ̨��
	 */
	struct DetectPlatformEntity : public AbstractTable {
		DetectPlatformEntity() :AbstractTable("detect_platform_entity") {}

		QString id = "id";
		QString name = "name";
	};

	/*!
	 * @brief ���ƽ̨���ͱ�
	 */
	struct DetectPlatformSubtypeEntity : public AbstractTable {
		DetectPlatformSubtypeEntity() :AbstractTable("detect_platform_subtype_entity") {}

		QString id = "id";
		QString detectId = "detect_id";
		QString name = "name";
	};

	/*!
	 * @brief �������ƽ̨��
	 */
	struct TaskDetectPlatformEntity : public AbstractTable {
		TaskDetectPlatformEntity() :AbstractTable("task_detect_platform_entity") {}

		QString id = "id";
		QString taskId = "task_id";
		QString detectId = "detect_id";
		QString name = "name";
		QString sensorType = "sensor_type";
		QString platformPower = "platform_power";
		QString startTime = "start_time";
		QString endTime = "end_time";
		QString lastTime = "last_time";
	};

	/*!
	* @brief ֵ����־��Ϣ��
	*/
	struct DutyRecordEntity : public AbstractTable {
		DutyRecordEntity() :AbstractTable("task_duty_record") {}

		QString id = "id";
		QString taskId = "task_id";
		QString createTime = "create_time";
		QString description = "description";
		QString seaCondition = "sea_condition";
		QString wind = "wind";
		QString windSpeed = "wind_speed";
		QString waveHigh = "wave_high";
		QString oceanCurrents = "ocean_currents";
	};

	/*!
	* @brief �����¼��Ϣ��
	*/
	struct ExperimentRecordEntity : public AbstractTable {
		ExperimentRecordEntity() :AbstractTable("task_experiment_record") {}

		QString id = "id";
		QString taskId = "task_id";
		QString platformId = "platform_id";
		QString floatingTime = "floating_time";
		QString lon = "lon";
		QString lat = "lat";
		QString setHeadingDegree = "set_heading_degree";
		QString actualHeadingDegree = "actual_heading_degree";
		QString acousticState = "acoustic_state";
		QString targetNum = "target_num";
		QString underwaterTargetNum = "underwater_target_num";
		QString underwaterTargetInfo = "underwater_target_info";
		QString maxDepth = "max_depth";
		QString profileIndex = "profile_index";
		QString profileLength = "profile_length";
		QString profileDistance = "profile_distance";
	};


}	//namespace Table
