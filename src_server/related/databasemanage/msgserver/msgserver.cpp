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
	 * @brief ����Ӧ���ͻؿͻ���
	 * @details �����ݿͻ��˽���Ϣ���ɵ����Ĵ����̴߳����������������Ϊ�漰���߳�֮���client�ķ��ʣ�
				������Ҫ����
	 * @param unit ��������Ӧ
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
	 * @brief �����¿ͻ�����������
	 * @param remoteClient �ͻ�������
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
	 * @brief �ͻ��˽����������ݺ�ص�
	 * @param remoteClient �������ݵĿͻ���
	 * @param data ��������ʼ��ַ
	 * @param dataLen �������ݵĳ���
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