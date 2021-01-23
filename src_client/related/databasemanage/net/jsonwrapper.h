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

#include <QObject>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <commondefines/protocol.h>

namespace Related {

	class JsonWrapper : public QObject
	{
		Q_OBJECT

	public:
		static JsonWrapper * instance();
		~JsonWrapper();

		QByteArray wrap(Datastruct::PacketType type, const Datastruct::UserLoginRequest & request);

		void unwrap(const QByteArray & data);

	private:
		JsonWrapper(QObject *parent = nullptr);

	private:


	private:
		static JsonWrapper * m_instance;

	};

} //namespace Related 