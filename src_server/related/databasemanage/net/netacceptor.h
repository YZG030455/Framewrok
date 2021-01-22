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

#include <network/libuv/uv_eventloop.h>
#include <network/libuv/uv_tcpserver.h>

#include "../datastruct.h"
#include "../net/protocol.h"

namespace Related {

	class NetAcceptor : public QObject
	{
		Q_OBJECT

	public:
		static NetAcceptor * instance();
		~NetAcceptor();

		void start(QString localIp,ushort localPort);

		void processResponseUnit(ResponseUnit * unit);

	private:
		NetAcceptor(QObject *parent = nullptr);

		void newTcpConnectionCallback(Network::AcceptTcpClient * remoteClient);
		void newMessageCallback(Network::AcceptTcpClient * remoteClient, const char* data, int dataLen);

		bool searchNextPackHead(Base::RFixedRingBuffer & ringBuffer);

	private:
		static NetAcceptor * m_instance;

		QMap<int, RemoteClientInfo * > m_clients;		/*!< key:���ӱ�ţ�value:�ͻ������Ӿ�� */

		Network::Uv_EventLoop * m_dataEventLoop;		/*!< ����ģ���¼�ѭ�� */
		Network::Uv_TcpServer * m_dataTcpServer;		/*!< ����ģ��Tcp������ */

	};

} //namespace Related 