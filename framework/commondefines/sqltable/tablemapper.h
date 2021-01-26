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
		QString detectPlatform = "detect_platform";
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
	};

	/*!
	* @brief �����¼��Ϣ��
	*/
	struct ExperimentRecordEntity : public AbstractTable {
		ExperimentRecordEntity() :AbstractTable("task_experiment_record") {}

		QString id = "id";
		QString taskId = "task_id";
		QString platformId = "platform_id";
		QString lon = "lon";
		QString lat = "lat";
		QString seaCondition = "sea_condition";
		QString floatingTime = "floating_time";
	};


}	//namespace Table
