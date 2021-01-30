#include "netacceptor.h"

#include <QDebug>
#include "../global.h"

namespace Related {

	NetAcceptor * NetAcceptor::m_instance = nullptr;

	NetAcceptor::NetAcceptor(QObject *parent)
		: QObject(parent)
	{
	}

	NetAcceptor * NetAcceptor::instance()
	{
		if (m_instance == nullptr)
			m_instance = new NetAcceptor();

		return m_instance;
	}

	NetAcceptor::~NetAcceptor()
	{
	}

	void NetAcceptor::start(QString localIp, ushort localPort)
	{
		m_dataEventLoop = new Network::Uv_EventLoop();

		m_dataTcpServer = new Network::Uv_TcpServer(m_dataEventLoop->eventLoop());
		m_dataTcpServer->setNewConnectionCallBack(std::bind(&NetAcceptor::newTcpConnectionCallback, this, std::placeholders::_1));
		m_dataTcpServer->setMessageRecvCallback(std::bind(&NetAcceptor::newMessageCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

		m_dataTcpServer->start(localIp.toStdString(), localPort);
		m_dataEventLoop->startLoop();
	}

	void NetAcceptor::processResponseUnit(ResponseUnit * unit)
	{
		{
			QMutexLocker locker(&m_clientMutex);

			if (m_clients.contains(unit->m_clientId)) {
				RemoteClientInfoPtr client = m_clients.value(unit->m_clientId);
				client->m_tcpClient->send(unit->m_resposneData.data(), unit->m_resposneData.size());
			}
		}

		delete unit;
	}

	/*!
	 * @brief �����¿ͻ�����������
	 * @param remoteClient �ͻ�������
	 */
	void NetAcceptor::newTcpConnectionCallback(Network::AcceptTcpClient * remoteClient)
	{
		RemoteClientInfoPtr ptr(new RemoteClientInfo());
		ptr->m_tcpClient = remoteClient;

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
	void NetAcceptor::newMessageCallback(Network::AcceptTcpClient * remoteClient, const char* data, int dataLen)
	{
		RemoteClientInfoPtr clientInfo;
		{
			QMutexLocker locker(&m_clientMutex);
			if (!m_clients.contains(remoteClient->id())) {
				return;
			}

			clientInfo = m_clients.value(remoteClient->id());
		}

		clientInfo->m_recvRingBuffer.append(data, dataLen);

		Datastruct::PacketHead packHead;
		int packHeadLen = sizeof(Datastruct::PacketHead);

		if (clientInfo->m_recvRingBuffer.dataSize() > packHeadLen)
		{
			do
			{
				clientInfo->m_recvRingBuffer.preRead((char *)&packHead, packHeadLen);

				if (packHead.m_magicHead == PACK_HEAD)
				{
					//[1]���ٴ��ڶ���һ���������ݰ�
					if (packHead.m_dataLen <= clientInfo->m_recvRingBuffer.dataSize())
					{
						int endCode = 0;
						//NOTE 20190711 ���յ����ݳ���Ϊ0ʱ��������Ѱ����һ������ͷ
						int t_offsetRead = packHead.m_dataLen - sizeof(Datastruct::PacketTail);
						if (t_offsetRead > 0) {
							clientInfo->m_recvRingBuffer.preRead(t_offsetRead, (char *)&endCode, sizeof(int));
						}
						else {
							if (searchNextPackHead(clientInfo->m_recvRingBuffer))
								continue;
						}

						//NOTE 20190710 ��û���ҵ�β��־ʱ��Ӧ�ôӵ�ǰλ�ÿ�ʼȥ������һ����ʼ��ʶ��������������һֱ�ѻ�
						if (endCode != PACK_TAIL) {
							qDebug() << "start search next frame:" << packHead.m_packetType << packHead.m_dataLen << clientInfo->m_recvRingBuffer.dataSize();
							if (searchNextPackHead(clientInfo->m_recvRingBuffer))
								continue;
							else
								return;
						}

						//��װ�������󣬼��봦����У�����ͳһ����
						RequestUnit * unit = new RequestUnit();
						unit->m_clientId = remoteClient->id();
						unit->m_requestData.resize(packHead.m_dataLen);
						clientInfo->m_recvRingBuffer.read(unit->m_requestData.data(), packHead.m_dataLen);

						G_RequestQuque.put(unit);

						if (clientInfo->m_recvRingBuffer.dataSize() <= 0)
							break;

						if (clientInfo->m_recvRingBuffer.dataSize() >= packHeadLen)
							continue;
					}
					else {
						break;
					}
				}
				else
				{
					if (searchNextPackHead(clientInfo->m_recvRingBuffer))
						continue;
					else
						return;
				}
			} while (clientInfo->m_recvRingBuffer.dataSize() > 0);
		}
	}

	bool NetAcceptor::searchNextPackHead(Base::RFixedRingBuffer & ringBuffer)
	{
		qint64 t_iHasSearchLen = 1;
		int t_iPackHeadLen = sizeof(Datastruct::PacketHead);
		Datastruct::PacketHead t_packHead;

		uint dd = PACK_HEAD;

		while (t_iHasSearchLen <= ringBuffer.dataSize() - t_iPackHeadLen)
		{
			ringBuffer.preRead(t_iHasSearchLen, (char *)&t_packHead, t_iPackHeadLen);
			if (t_packHead.m_magicHead == PACK_HEAD)
			{
				qDebug() << "++searchNextPackHead data:" << t_iHasSearchLen;
				ringBuffer.skipRead(t_iHasSearchLen);
				return true;
			}
			++t_iHasSearchLen;
		}

		if (ringBuffer.dataSize() > t_iHasSearchLen) {
			ringBuffer.skipRead(t_iHasSearchLen);
		}

		return false;
	}

} //namespace Related 