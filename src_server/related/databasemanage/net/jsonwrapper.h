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

#include "protocol.h"

namespace Related {

	class JsonWrapper : public QObject
	{
		Q_OBJECT

	public:
		static JsonWrapper * instance();
		~JsonWrapper();

		QByteArray wrap(PacketType type, const UserLoginRequest & request);
		bool unrap(const QByteArray & data, UserLoginRequest & request);

		QByteArray wrap(PacketType type, const UserLoginResponse & response);
		bool unrap(const QByteArray & data, UserLoginResponse & response);

	private:
		JsonWrapper(QObject *parent = nullptr);

		/*! 
		 * @brief ��JSON��ԭʼ���ݽ�����������ûص�������
		 * @param data ����ԭʼ����
		 * @param callback �ص�������
		 * @return true:����ɹ�;false:���ʧ��
		 */
		bool unwrapObject(const QByteArray & data,std::function<void(QJsonObject &)> callback);

	private:
		static JsonWrapper * m_instance;

	};

} //namespace Related 