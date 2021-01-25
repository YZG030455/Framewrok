/*!
 * @brief     �ź���תվ
 * @details   ���������紦��͸���ҳ��֮�佨���ź�����,����ͳһ���ź����ӽӿ�
 * @author    wey
 * @version   1.0
 * @date      2021.01.22 08:05:25
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
 #pragma once

#include <QObject>

#include <commondefines/protocol.h>

namespace Related {

	class SignalDispatch : public QObject
	{
		Q_OBJECT

	public:
		static SignalDispatch * instance();
		~SignalDispatch();

		void recvUserLoginResponse(const Datastruct::UserLoginResponse & response);
		void recvUseRegistResponse(const Datastruct::UserRegistResponse & response);
		void recvQueryUserListResponse(const Datastruct::LoadAllUserResponse & response);
		void recvOperateUserResponse(const Datastruct::OperateUserResponse & response);

	signals:
		void respUserLoginResponse(const Datastruct::UserLoginResponse & response);
		void respUserRegistResponse(const Datastruct::UserRegistResponse & response);
		void respQueryUserListResponse(const Datastruct::LoadAllUserResponse & response);
		void resOperateUserResponse(const Datastruct::OperateUserResponse & response);

	private:
		SignalDispatch(QObject *parent = nullptr);


	private:
		static SignalDispatch * m_instance;

		friend class JsonWrapper;
	};

} //namespace Related 