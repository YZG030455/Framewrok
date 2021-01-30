/*!
 * @brief     �������ӽ�����
 * @details   ���ڴ���tcp�����������տͻ�������
 * @author    wey
 * @version   1.0
 * @date      2021.01.22 14:45:06
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
 #pragma once

#include <QObject>
#include <QSharedPointer>
#include <QMutex>

#include <commondefines/protocol.h>
#include <network/libuv/uv_eventloop.h>
#include <network/libuv/uv_tcpserver.h>

#include "clientsession.h"
#include "../datastruct.h"

namespace Related {

	typedef QSharedPointer<ClientSession> ClientSessionPtr;

	class MsgServer : public QObject
	{
		Q_OBJECT

	public:
		static MsgServer * instance();
		~MsgServer();

		void start(QString localIp,ushort localPort);

		void processResponseUnit(ResponseUnit * unit);

	private:
		MsgServer(QObject *parent = nullptr);

		void newTcpConnectionCallback(Network::AcceptTcpClient * remoteClient);
		void newMessageCallback(Network::AcceptTcpClient * remoteClient, const char* data, int dataLen);

	private:
		static MsgServer * m_instance;

		QMap<int, ClientSessionPtr> m_clients;		/*!< key:���ӱ�ţ�value:�ͻ������Ӿ�� */

		Network::Uv_EventLoop * m_dataEventLoop;		/*!< ����ģ���¼�ѭ�� */
		Network::Uv_TcpServer * m_dataTcpServer;		/*!< ����ģ��Tcp������ */
		QMutex m_clientMutex;
	};

} //namespace Related 