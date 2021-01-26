#include "netconnector.h"

#include <QThread>
#include <QDebug>

#include <commondefines/wrapper/jsonwrapper.h>
#include "signaldispatch.h"

using namespace CommonDefines;

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

		Datastruct::PacketHead packHead;
		int packHeadLen = sizeof(Datastruct::PacketHead);

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
						int t_offsetRead = packHead.m_dataLen - sizeof(Datastruct::PacketTail);
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
	* @details �ڽ�����������ʱ�����ܽ��յ������ݰ��򳤶����⣬δ��ȷ�ҵ���β��������ʱ�����������ݻ�һֱ�ѻ�����������޷���������
	*          ��Ҫ�ӵ�ǰ�Ѷ�ȡλ�ü���������һ�����ݰ�ͷ��ֱ���ҵ���ȷ�����ݰ�ͷ
	* @return true���ҵ���һ�����ݰ�ͷ��
	*         false���ڵ�ǰ���ݻ�������δ�ҵ����ݰ�ͷ
	*/
	bool NetConnector::searchNextPackHead()
	{
		qint64 t_iHasSearchLen = 1;
		int t_iPackHeadLen = sizeof(Datastruct::PacketHead);
		Datastruct::PacketHead t_packHead;
		
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

	bool NetConnector::connectTo(QString remoteIp, ushort remotePort)
	{
		return m_dataTcpClient->connect(remoteIp.toStdString(), remotePort);
	}

	bool NetConnector::isConnected()
	{
		return m_dataTcpClient->connected();
	}

	void NetConnector::write(const Datastruct::UserLoginRequest & request)
	{
		QByteArray array = makePacket(Datastruct::P_UserLogin ,CommonDefines::JsonWrapper::instance()->wrap(request));
		sendData(array);
	}

	void NetConnector::write(const Datastruct::UserRegistRequest & request)
	{
		QByteArray array = makePacket(Datastruct::P_UserRegist, CommonDefines::JsonWrapper::instance()->wrap(request));
		sendData(array);
	}

	void NetConnector::write(const Datastruct::LoadAllUserRequest & request)
	{
		QByteArray array = makePacket(Datastruct::P_UserList, CommonDefines::JsonWrapper::instance()->wrap(request));
		sendData(array);
	}

	void NetConnector::write(const Datastruct::OperateUserRequest & request)
	{
		QByteArray array = makePacket(Datastruct::P_UserOperate, CommonDefines::JsonWrapper::instance()->wrap(request));
		sendData(array);
	}

	void NetConnector::write(const Datastruct::TaskCreateRequest & request)
	{
		QByteArray array = makePacket(Datastruct::P_CreateTask, CommonDefines::JsonWrapper::instance()->wrap(request));
		sendData(array);
	}

	void NetConnector::write(const Datastruct::LoadAllTaskRequest & request)
	{
		QByteArray array = makePacket(Datastruct::P_TaskList, CommonDefines::JsonWrapper::instance()->wrap(request));
		sendData(array);
	}

	void NetConnector::write(const Datastruct::TaskDeleteRequest & request)
	{
		QByteArray array = makePacket(Datastruct::P_TaskDelete, CommonDefines::JsonWrapper::instance()->wrap(request));
		sendData(array);
	}

	void NetConnector::write(const Datastruct::DutyRecordCreateRequest & request)
	{
		QByteArray array = makePacket(Datastruct::P_CreateDutyRecord, CommonDefines::JsonWrapper::instance()->wrap(request));
		sendData(array);
	}

	void NetConnector::write(const Datastruct::LoadAllDutyRecordRequest & request)
	{
		QByteArray array = makePacket(Datastruct::P_ListDutyRecords, CommonDefines::JsonWrapper::instance()->wrap(request));
		sendData(array);
	}

	void NetConnector::write(const Datastruct::DutyRecordDeleteRequest & request)
	{
		QByteArray array = makePacket(Datastruct::P_DeleteDutyRecords, CommonDefines::JsonWrapper::instance()->wrap(request));
		sendData(array);
	}

	void NetConnector::write(const Datastruct::ExperimentRecordCreateRequest & request)
	{
		QByteArray array = makePacket(Datastruct::P_CreateExperimentRecord, CommonDefines::JsonWrapper::instance()->wrap(request));
		sendData(array);
	}

	void NetConnector::write(const Datastruct::LoadAllExperimentRecordsRequest & request)
	{
		QByteArray array = makePacket(Datastruct::P_ListExperimentRecords, CommonDefines::JsonWrapper::instance()->wrap(request));
		sendData(array);
	}

	void NetConnector::write(const Datastruct::ExperimentRecordDeleteRequest & request)
	{
		QByteArray array = makePacket(Datastruct::P_DeleteExperimentRecord, CommonDefines::JsonWrapper::instance()->wrap(request));
		sendData(array);
	}
	
	QByteArray NetConnector::makePacket(Datastruct::PacketType type, QByteArray & body)
	{
		static int headLen = sizeof(Datastruct::PacketHead);
		static int tailLen = sizeof(Datastruct::PacketTail);

		Datastruct::PacketHead phead;
		phead.m_packetType = type;
		phead.m_dataLen = headLen + body.length() + tailLen;

		Datastruct::PacketTail ptail;

		QByteArray data;
		data.append((char *)&phead, headLen);
		data.append(body);
		data.append((char *)&ptail, tailLen);

		return data;
	}

	/*! 
	 * @brief ͨ�����緢������
	 * @param data ���������ݵ�Ԫ
	 */
	void NetConnector::sendData(const QByteArray & data)
	{
		m_dataTcpClient->send(data.data(), data.length());
	}

	/*!
	 * @brief ������������������
	 * @param array �������˷�������
	 */
	void NetConnector::respRectNetData(QByteArray array)
	{
		Datastruct::PacketHead head;
		memcpy((char *)&head, array.data(), sizeof(Datastruct::PacketHead));

		QByteArray jsonData(array.data() + sizeof(head), array.size() - sizeof(Datastruct::PacketHead) - sizeof(Datastruct::PacketTail));

		switch (head.m_packetType)
		{
			case Datastruct::P_UserLogin: {
				Datastruct::UserLoginResponse response;
				if (CommonDefines::JsonWrapper::instance()->unrap(jsonData, response)) {
					SignalDispatch::instance()->recvUserLoginResponse(response);
				}
			}
				break;

			case Datastruct::P_UserRegist: {
				Datastruct::UserRegistResponse response;
				if (CommonDefines::JsonWrapper::instance()->unrap(jsonData, response)) {
					SignalDispatch::instance()->recvUseRegistResponse(response);
				}
			}
				break;

			case Datastruct::P_UserList: {
				Datastruct::LoadAllUserResponse response;
				if (CommonDefines::JsonWrapper::instance()->unrap(jsonData, response)) {
					SignalDispatch::instance()->recvQueryUserListResponse(response);
				}
			}
				break;

			case Datastruct::P_UserOperate: {
				Datastruct::OperateUserResponse response;
				if (CommonDefines::JsonWrapper::instance()->unrap(jsonData, response)) {
					SignalDispatch::instance()->recvOperateUserResponse(response);
				}
			}
				break;
			case  Datastruct::P_CreateTask: {
				Datastruct::TaskCreateResponse response;
				if (CommonDefines::JsonWrapper::instance()->unrap(jsonData, response)) {
					SignalDispatch::instance()->recvTaskCreateResponse(response);
				}
			}
				break;

			case  Datastruct::P_TaskList: {
				Datastruct::LoadAllTaskResponse response;
				if (CommonDefines::JsonWrapper::instance()->unrap(jsonData, response)) {
					SignalDispatch::instance()->recvQueryAllTaskResponse(response);
				}
			}
				break;

			case  Datastruct::P_TaskDelete: {
				Datastruct::TaskDeleteResponse response;
				if (CommonDefines::JsonWrapper::instance()->unrap(jsonData, response)) {
					SignalDispatch::instance()->recvTaskDeleteResponse(response);
				}
			}
				break;

			case  Datastruct::P_CreateDutyRecord: {
				Datastruct::DutyRecordCreateResponse response;
				if (CommonDefines::JsonWrapper::instance()->unrap(jsonData, response)) {
					SignalDispatch::instance()->recvDutyRecordCreateResponse(response);
				}
			}
				break;

			case  Datastruct::P_ListDutyRecords: {
				Datastruct::LoadAllDutyRecordResponse response;
				if (CommonDefines::JsonWrapper::instance()->unrap(jsonData, response)) {
					SignalDispatch::instance()->recvQueryAllDutyRecordResponse(response);
				}
			}
				break;

			case  Datastruct::P_DeleteDutyRecords: {
				Datastruct::DutyRecordDeleteResponse response;
				if (CommonDefines::JsonWrapper::instance()->unrap(jsonData, response)) {
					SignalDispatch::instance()->recvDutyRecordDeleteResponse(response);
				}
			}
				break;

			case  Datastruct::P_CreateExperimentRecord: {
				Datastruct::ExperimentRecordCreateResponse response;
				if (CommonDefines::JsonWrapper::instance()->unrap(jsonData, response)) {
					SignalDispatch::instance()->recvExperimentRecordCreateResponse(response);
				}
			}
				break;

			case  Datastruct::P_ListExperimentRecords: {
				Datastruct::LoadAllExperimentRecordsResponse response;
				if (CommonDefines::JsonWrapper::instance()->unrap(jsonData, response)) {
					SignalDispatch::instance()->recvQueryAllExperimentRecordResponse(response);
				}
			}
				break;
			case  Datastruct::P_DeleteExperimentRecord: {
				Datastruct::ExperimentRecordDeleteResponse response;
				if (CommonDefines::JsonWrapper::instance()->unrap(jsonData, response)) {
					SignalDispatch::instance()->recvExperimentRecordDeleteResponse(response);
				}
			}
				break;

			default:
				break;
		}
	}

} //namespace Related 