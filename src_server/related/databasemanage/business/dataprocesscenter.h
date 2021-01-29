/*!
 * @brief     ���������������ҵ�񣬲�����ִ�н��   
 * @author    wey
 * @version   1.0
 * @date      2021.01.23 10:06:22
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
 #pragma once

#include <QObject>

#include <base\util\rutil.h>

#include <commondefines/protocol.h>
#include <base\common\sql\databasemanager.h>

namespace Related {

	class DataProcessCenter : public QObject
	{
		Q_OBJECT

	public:
		DataProcessCenter(QObject *parent = nullptr);
		~DataProcessCenter();
		
		/*! 
		 * @brief �����ݿ����ӡ�ÿ���̵߳����ݿ�����ֻ���ڵ�ǰ�߳���ʹ�á�
		 * @param db ���ݿ����Ӿ��
		 */
		void bindDatabase(Base::Database * db);

		Datastruct::UserLoginResponse processUserLogin(int clientId,const Datastruct::UserLoginRequest & request);
		Datastruct::UserRegistResponse processUserRegist(int clientId,const Datastruct::UserRegistRequest & request);
		Datastruct::LoadAllUserResponse processUserList(int clientId,const Datastruct::LoadAllUserRequest & request);
		Datastruct::OperateUserResponse processUserOperate(int clientId,const Datastruct::OperateUserRequest & request);

		// �й�����
		Datastruct::TaskCreateResponse  processTaskCreate(int clientId, const Datastruct::TaskCreateRequest & request);
		Datastruct::LoadAllTaskResponse processTaskList(int clientId, const Datastruct::LoadAllTaskRequest & request);
		Datastruct::TaskDeleteResponse processTaskDelete(int clientId, const Datastruct::TaskDeleteRequest & request);
		Datastruct::TaskSimpleResponse processTaskSimple(int clientId, const Datastruct::TaskSimpleRequest & request);

		//ֵ����־
		Datastruct::DutyRecordCreateResponse  processDutyRecordCreate(int clientId, const Datastruct::DutyRecordCreateRequest & request);
		Datastruct::LoadAllDutyRecordResponse processDutyRecordList(int clientId, const Datastruct::LoadAllDutyRecordRequest & request);
		Datastruct::DutyRecordDeleteResponse processDutyRecordDelete(int clientId, const Datastruct::DutyRecordDeleteRequest & request);
		Datastruct::DutyRecordModifyResponse processDutyRecordModify(int clientId, const Datastruct::DutyRecordModifyRequest & request);

		//�����¼
		Datastruct::ExperimentRecordCreateResponse  processExperimentRecordCreate(int clientId, const Datastruct::ExperimentRecordCreateRequest & request);
		Datastruct::LoadAllExperimentRecordsResponse processExperimentRecordList(int clientId, const Datastruct::LoadAllExperimentRecordsRequest & request);
		Datastruct::ExperimentRecordDeleteResponse  processExperimentRecordDelete(int clientId, const Datastruct::ExperimentRecordDeleteRequest & request);
		Datastruct::ExperimentRecordModifyResponse processExperimentRecordModify(int clientId, const Datastruct::ExperimentRecordModifyRequest & request);

		//ƽ̨��Ϣ
		Datastruct::DetectPlatformCreateResponse  processDetectPlatformCreate(int clientId, const Datastruct::DetectPlatformCreateRequest & request);
		Datastruct::LoadAllDetectPlatformsResponse processDetectPlatformList(int clientId, const Datastruct::LoadAllDetectPlatformsRequest & request);
		Datastruct::DetectPlatformDeleteResponse  processDetectPlatformDelete(int clientId, const Datastruct::DetectPlatformDeleteRequest & request);
		Datastruct::DetectPlatformModifyResponse processDetectPlatformModify(int clientId, const Datastruct::DetectPlatformModifyRequest & request);

		//ƽ̨������Ϣ
		Datastruct::DetectPlatformSubtypeCreateResponse  processDetectPlatformSubtypeCreate(int clientId, const Datastruct::DetectPlatformSubtypeCreateRequest & request);
		Datastruct::LoadAllDetectPlatformSubtypesResponse processDetectPlatformSubtypeList(int clientId, const Datastruct::LoadAllDetectPlatformSubtypesRequest & request);
		Datastruct::DetectPlatformSubtypeDeleteResponse  processDetectPlatformSubtypeDelete(int clientId, const Datastruct::DetectPlatformSubtypeDeleteRequest & request);
		Datastruct::DetectPlatformSubtypeModifyResponse processDetectPlatformSubtypeModify(int clientId, const Datastruct::DetectPlatformSubtypeModifyRequest & request);

	private:
		Base::Database * m_database;

	};

} //