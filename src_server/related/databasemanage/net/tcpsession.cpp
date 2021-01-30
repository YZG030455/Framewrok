#include "tcpsession.h"

#include <QDebug>

namespace Related {

	TcpSession::TcpSession(Network::AcceptTcpClient * client)
		: m_tcpClient(client)
	{
	}

	TcpSession::~TcpSession()
	{
	}

	void TcpSession::sendData(const char * data, int dataLength)
	{
		m_tcpClient->send(data, dataLength);
	}

	void TcpSession::recvData(const char * data, int dataLength)
	{
		m_recvRingBuffer.append(data, dataLength);

		Datastruct::PacketHead packHead;
		int packHeadLen = sizeof(Datastruct::PacketHead);

		if (m_recvRingBuffer.dataSize() > packHeadLen)
		{
			do
			{
				m_recvRingBuffer.preRead((char *)&packHead, packHeadLen);

				if (packHead.m_magicHead == PACK_HEAD)
				{
					//[1]���ٴ��ڶ���һ���������ݰ�
					if (packHead.m_dataLen <= m_recvRingBuffer.dataSize())
					{
						int endCode = 0;
						//NOTE 20190711 ���յ����ݳ���Ϊ0ʱ��������Ѱ����һ������ͷ
						int t_offsetRead = packHead.m_dataLen - sizeof(Datastruct::PacketTail);
						if (t_offsetRead > 0) {
							m_recvRingBuffer.preRead(t_offsetRead, (char *)&endCode, sizeof(int));
						}
						else {
							if (searchNextPackHead())
								continue;
						}

						//NOTE 20190710 ��û���ҵ�β��־ʱ��Ӧ�ôӵ�ǰλ�ÿ�ʼȥ������һ����ʼ��ʶ��������������һֱ�ѻ�
						if (endCode != PACK_TAIL) {
							qDebug() << "start search next frame:" << packHead.m_packetType << packHead.m_dataLen <<m_recvRingBuffer.dataSize();
							if (searchNextPackHead())
								continue;
							else
								return;
						}

						//NOTE ������Ѿ���ȥ����ͷ��β�������������д���
						QByteArray dataArray;
						dataArray.resize(packHead.m_dataLen);
						m_recvRingBuffer.read(dataArray.data(), packHead.m_dataLen);

						processData(dataArray);

						if (m_recvRingBuffer.dataSize() <= 0)
							break;

						if (m_recvRingBuffer.dataSize() >= packHeadLen)
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
			} while (m_recvRingBuffer.dataSize() > 0);
		}
	}

	bool TcpSession::searchNextPackHead()
	{
		qint64 t_iHasSearchLen = 1;
		int t_iPackHeadLen = sizeof(Datastruct::PacketHead);
		Datastruct::PacketHead t_packHead;

		uint dd = PACK_HEAD;

		while (t_iHasSearchLen <= m_recvRingBuffer.dataSize() - t_iPackHeadLen)
		{
			m_recvRingBuffer.preRead(t_iHasSearchLen, (char *)&t_packHead, t_iPackHeadLen);
			if (t_packHead.m_magicHead == PACK_HEAD)
			{
				qDebug() << "++searchNextPackHead data:" << t_iHasSearchLen;
				m_recvRingBuffer.skipRead(t_iHasSearchLen);
				return true;
			}
			++t_iHasSearchLen;
		}

		if (m_recvRingBuffer.dataSize() > t_iHasSearchLen) {
			m_recvRingBuffer.skipRead(t_iHasSearchLen);
		}

		return false;
	}

} //namespace Related 