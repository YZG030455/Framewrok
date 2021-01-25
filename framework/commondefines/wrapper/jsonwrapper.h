/*!
 * @brief     ������ת����JSON��ʽ������������ݰ�   
 * @author    wey
 * @version   1.0
 * @date      2021.01.21 15:09:58
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
 #pragma once

#include <functional>

#include <QObject>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "../protocol.h"
#include "../commondefines_global.h"
#include "jsonkey.h"

namespace CommonDefines {

	class COMMONDEFINESHARED_EXPORT JsonWrapper : public QObject
	{
		Q_OBJECT

	public:
		static JsonWrapper * instance();
		~JsonWrapper();

		QByteArray wrap(const Datastruct::UserLoginRequest & request);
		bool unrap(const QByteArray & data, Datastruct::UserLoginRequest & request); 

		QByteArray wrap(const Datastruct::UserLoginResponse & response);
		bool unrap(const QByteArray & data, Datastruct::UserLoginResponse & response);

		QByteArray wrap(const Datastruct::UserRegistRequest & request);
		bool unrap(const QByteArray & data, Datastruct::UserRegistRequest & request);

		QByteArray wrap(const Datastruct::UserRegistResponse & response);
		bool unrap(const QByteArray & data, Datastruct::UserRegistResponse & response); 
		
		QByteArray wrap(const Datastruct::LoadAllUserRequest & request);
		bool unrap(const QByteArray & data, Datastruct::LoadAllUserRequest & request);

		QByteArray wrap(const Datastruct::LoadAllUserResponse & response);
		bool unrap(const QByteArray & data, Datastruct::LoadAllUserResponse & response);

	private:
		JsonWrapper(QObject *parent = nullptr);

		/*! 
		 * @brief ��JSON��ԭʼ���ݽ�����������ûص�������
		 * @param data ����ԭʼ����
		 * @param callback �ص�������
		 * @return true:����ɹ�;false:���ʧ��
		 */
		bool unwrapObject(const QByteArray & data,std::function<void(QJsonObject &)> callback);

		QByteArray wrapObject(std::function<void(QJsonObject &)> callback);

	private:
		static JsonWrapper * m_instance;
		JsonKey m_jsonKey;
	};

} //namespace CommonDefines 