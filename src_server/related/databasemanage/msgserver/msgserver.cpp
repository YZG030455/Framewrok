#include "msgserver.h"

#include <QDebug>

namespace Related {

	MsgServer * MsgServer::m_instance = nullptr;

	MsgServer::MsgServer(QObject *parent)
		: QObject(parent)
	{
	}

	MsgServer * MsgServer::instance()
	{
		if (m_instance == nullptr)
			m_instance = new MsgServer();

		return m_instance;
	}

	MsgServer::~MsgServer()
	{
	}

	void MsgServer::start(QString localIp, ushort localPort)
	{
		m_dataEventLoop = new Network::Uv_EventLoop();

		m_dataTcpServer = new Network::Uv_TcpServer(m_dataEventLoop->eventLoop());
		m_dataTcpServer->setNewConnectionCallBack(std::bind(&MsgServer::newTcpConnectionCallback, this, std::placeholders::_1));
		m_dataTcpServer->setMessageRecvCallback(std::bind(&MsgServer::newMessageCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

		m_dataTcpServer->start(localIp.toStdString(), localPort);
		m_dataEventLoop->startLoop();
	}

	/*! 
	 * @brief 将响应发送回客户端
	 * @details 因数据客户端将消息交由单独的处理线程处理，而处理结束后因为涉及到线程之间对client的访问，
				所以需要加锁
	 * @param unit 处理结果响应
	 */
	void MsgServer::processResponseUnit(ResponseUnit * unit)
	{
		{
			QMutexLocker locker(&m_clientMutex);

			if (m_clients.contains(unit->m_clientId)) {
				ClientSessionPtr client = m_clients.value(unit->m_clientId);
				client->sendData(unit->m_resposneData.data(), unit->m_resposneData.size());
			}
		}

		delete unit;
	}

	/*!
	 * @brief 接收新客户端连接请求
	 * @param remoteClient 客户端连接
	 */
	void MsgServer::newTcpConnectionCallback(Network::AcceptTcpClient * remoteClient)
	{
		ClientSessionPtr ptr(new ClientSession(remoteClient));

		{
			QMutexLocker locker(&m_clientMutex);
			m_clients.insert(remoteClient->id(), ptr);
		}
	}

	/*!
	 * @brief 客户端接收网络数据后回调
	 * @param remoteClient 发送数据的客户端
	 * @param data 数据区起始地址
	 * @param dataLen 接收数据的长度
	 */
	void MsgServer::newMessageCallback(Network::AcceptTcpClient * remoteClient, const char* data, int dataLen)
	{
		QMutexLocker locker(&m_clientMutex);
		if (!m_clients.contains(remoteClient->id())) {
			return;
		}

		ClientSessionPtr clientInfo = m_clients.value(remoteClient->id());
		clientInfo->recvData(data, dataLen);
	}

} //namespace Related 