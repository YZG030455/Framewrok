#include "netconnector.h"

#include <QThread>
#include <QDebug>

#include "jsonwrapper.h"

namespace Related {

	NetConnector * NetConnector::m_instance = nullptr;

	NetConnector::NetConnector(QObject *parent)
		: QObject(parent)
	{
		initNetwork();
		connect(this,SIGNAL(netRecvData(QByteArray)),this,SLOT(respRectNetData(QByteArray)));
	}

	void NetConnector::initNetwork()
	{
		m_eventLoop = new Network::Uv_EventLoop();
		m_dataTcpClient = new Network::Uv_TcpClient(m_eventLoop->eventLoop());
		m_dataTcpClient->setConnectedCallBack(std::bind(&NetConnector::connectCallBack, this, std::placeholders::_1));
		m_dataTcpClient->setCloseCallBack(std::bind(&NetConnector::closeCallBack, this, std::placeholders::_1));
		m_dataTcpClient->setRecvCallback(std::bind(&NetConnector::recvDataCallBack, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

		m_eventLoop->startLoop();
	}

	void NetConnector::connectCallBack(Network::Uv_TcpClient * client)
	{
		if (client == nullptr) {
			emit netConnected(false);
			return;
		}
		emit netConnected(true);
	}

	void NetConnector::closeCallBack(Network::Uv_TcpClient * client)
	{
		emit netConnected(false);
	}

	/*!
	 * @brief ������ջص�
	 * @param remoteClient ���ͷ���Ϣ
	 * @param data �������ݻ�������ʼ��ַ
	 * @param dataLen �������ݳ���
	 */
	void NetConnector::recvDataCallBack(Network::Uv_TcpClient * remoteClient, const char * data, int dataLen)
	{
		m_dataRecvRingBuffer.append(data, dataLen);

		PacketHead packHead;
		int packHeadLen = sizeof(PacketHead);

		if (m_dataRecvRingBuffer.dataSize() > packHeadLen)
		{
			do
			{
				m_dataRecvRingBuffer.preRead((char *)&packHead, packHeadLen);

				if (packHead.m_magicHead == PACK_HEAD)
				{
					//[1]���ٴ��ڶ���һ���������ݰ�
					if (packHead.m_dataLen <= m_dataRecvRingBuffer.dataSize())
					{
						int endCode = 0;
						//NOTE 20190711 ���յ����ݳ���Ϊ0ʱ��������Ѱ����һ������ͷ
						int t_offsetRead = packHead.m_dataLen - sizeof(PacketTail);
						if (t_offsetRead > 0) {
							m_dataRecvRingBuffer.preRead(t_offsetRead, (char *)&endCode, sizeof(int));
						}
						else {
							if (searchNextPackHead())
								continue;
						}

						//NOTE 20190710 ��û���ҵ�β��־ʱ��Ӧ�ôӵ�ǰλ�ÿ�ʼȥ������һ����ʼ��ʶ��������������һֱ�ѻ�
						if (endCode != PACK_TAIL) {
							qDebug() << "start search next frame:" << packHead.m_packetType << packHead.m_dataLen << m_dataRecvRingBuffer.dataSize();
							if (searchNextPackHead())
								continue;
							else
								return;
						}

						QByteArray array;
						array.resize(packHead.m_dataLen);
						m_dataRecvRingBuffer.read(array.data(), packHead.m_dataLen);

						//TODO 20210121 ֱ��ͨ�����ַ�ʽ�����Ǹ�ƿ��
						emit netRecvData(array);

						if (m_dataRecvRingBuffer.dataSize() <= 0)
							break;

						if (m_dataRecvRingBuffer.dataSize() >= packHeadLen)
							continue;
					}
					else {
						break;
					}
				}
				else
				{
					if (searchNextPackHead())
						continue;
					else
						return;
				}
			} while (m_dataRecvRingBuffer.dataSize() > 0);
		}
	}

	/*!
	* @brief �ӵ�ǰ���ݰ�λ�ÿ�ʼ����дһ�����ݰ�ͷ
	* @details �ڽ�����������ʱ�����ܽ��յ������ݰ��򳤶����⣬δ��ȷ�ҵ���β��������ʱ�������������ݻ�һֱ�ѻ�����������޷�����������
	*          ��Ҫ�ӵ�ǰ�Ѷ�ȡλ�ü���������һ�����ݰ�ͷ��ֱ���ҵ���ȷ�����ݰ�ͷ
	* @return true���ҵ���һ�����ݰ�ͷ��
	*         false���ڵ�ǰ���ݻ�������δ�ҵ����ݰ�ͷ
	*/
	bool NetConnector::searchNextPackHead()
	{
		qint64 t_iHasSearchLen = 1;
		int t_iPackHeadLen = sizeof(PacketHead);
		PacketHead t_packHead;
		
		uint dd = PACK_HEAD;

		while (t_iHasSearchLen <= m_dataRecvRingBuffer.dataSize() - t_iPackHeadLen)
		{
			m_dataRecvRingBuffer.preRead(t_iHasSearchLen, (char *)&t_packHead, t_iPackHeadLen);
			if (t_packHead.m_magicHead == PACK_HEAD)
			{
				qDebug() << "++searchNextPackHead data:" << t_iHasSearchLen;
				m_dataRecvRingBuffer.skipRead(t_iHasSearchLen);
				return true;
			}
			++t_iHasSearchLen;
		}

		if (m_dataRecvRingBuffer.dataSize() > t_iHasSearchLen) {
			m_dataRecvRingBuffer.skipRead(t_iHasSearchLen);
		}

		return false;
	}

	NetConnector * NetConnector::instance()
	{
		if (m_instance == nullptr) {
			m_instance = new NetConnector();
		}

		return m_instance;
	}

	NetConnector::~NetConnector()
	{
	}

	void NetConnector::connectTo(QString remoteIp, ushort remotePort)
	{
		m_dataTcpClient->connect(remoteIp.toStdString(), remotePort);
	}

	bool NetConnector::isConnected()
	{
		return m_dataTcpClient->connected();
	}

	void NetConnector::write(PacketType type, const UserLoginRequest & request)
	{
		QByteArray array = makePacket(type, JsonWrapper::instance()->wrap(type, request));

		m_dataTcpClient->send(array.data(), array.length());
	}

	QByteArray NetConnector::makePacket(PacketType type, QByteArray & body)
	{
		static int headLen = sizeof(PacketHead);
		static int tailLen = sizeof(PacketTail);

		PacketHead phead;
		phead.m_packetType = type;
		phead.m_dataLen = headLen + body.length() + tailLen;

		PacketTail ptail;

		QByteArray data;
		data.append((char *)&phead, headLen);
		data.append(body);
		data.append((char *)&ptail, tailLen);

		return data;
	}

	/*! 
	 * @brief �������������������
	 * @param array �������˷�������
	 */
	void NetConnector::respRectNetData(QByteArray array)
	{
		JsonWrapper::instance()->unwrap(array);
	}

} //namespace Related 