/*!
 * @brief     �����������ӹ���
 * @details   1.���𴴽��ͻ������ӣ����ӷ�������
			  2.������ͨ���ݰ�װ������
 * @author    wey
 * @version   1.0
 * @date      2021.01.20 16:06:15
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
 #pragma once

#include <QObject>
#include <QDateTime>

#include <base\util\rringbuffer.h>
#include <commondefines/protocol.h>
#include <network\libuv\uv_eventloop.h>
#include <network\libuv\uv_tcpclient.h>

namespace Related {

	class NetConnector : public QObject
	{
		Q_OBJECT
	public:
		static NetConnector * instance();
		~NetConnector();

		void setAutoReconnect(bool isAutoReconnect);

		/*! 
		 * @brief ������ָ����ip�Ͷ˿ںŷ�������
		 * @attention ���ô˷�������Ҫ�ȴ�����netConnected�źţ����ж϶�Ӧ�Ĳ������ſ���ȷ�������Ƿ����ӳɹ�
		 * @param remoteIp Զ�̷�����IP
		 * @param remotePort Զ�̷������˿ں�
		 * @return true:���óɹ������������������ӳɹ���false:����ʧ��
		 */
		bool connectTo(QString remoteIp,ushort remotePort);

		/*! 
		 * @brief ������������������Ƿ���
		 * @return true:�ѽ����������ӣ�false:δ������������
		 */
		bool isConnected();

		/*!
		 * @brief   �û��й�
		 */
		void write(const Datastruct::UserLoginRequest & request);
		void write(const Datastruct::UserRegistRequest & request);
		void write(const Datastruct::LoadAllUserRequest & request);
		void write(const Datastruct::OperateUserRequest & request);

		/*!
		 * @brief ��������й�
		 */
		void write(const Datastruct::TaskCreateRequest & request);
		void write(const Datastruct::LoadAllTaskRequest & request);
		void write(const Datastruct::TaskDeleteRequest & request);
		void write(const Datastruct::TaskSimpleRequest & request);
		
		/*!
		 * @brief  ֵ����־�й�
		 */
		void write(const Datastruct::DutyRecordCreateRequest & request);
		void write(const Datastruct::LoadAllDutyRecordRequest & request);
		void write(const Datastruct::DutyRecordDeleteRequest & request);
		void write(const Datastruct::DutyRecordModifyRequest & request);
		
		/*!
		 * @brief   �����¼�й�
		 */
		void write(const Datastruct::ExperimentRecordCreateRequest & request);
		void write(const Datastruct::LoadAllExperimentRecordsRequest & request);
		void write(const Datastruct::ExperimentRecordDeleteRequest & request);
		void write(const Datastruct::ExperimentRecordModifyRequest & request);
		
		/*!
		 * @brief   ���ƽ̨�й�
		 */
		void write(const Datastruct::DetectPlatformCreateRequest & request);
		void write(const Datastruct::LoadAllDetectPlatformsRequest & request);
		void write(const Datastruct::DetectPlatformDeleteRequest & request);
		void write(const Datastruct::DetectPlatformModifyRequest & request);

		/*!
		 * @brief   ���ƽ̨�����й�
		 */
		void write(const Datastruct::DetectPlatformSubtypeCreateRequest & request);
		void write(const Datastruct::LoadAllDetectPlatformSubtypesRequest & request);
		void write(const Datastruct::DetectPlatformSubtypeDeleteRequest & request);
		void write(const Datastruct::DetectPlatformSubtypeModifyRequest & request);

	signals:
		void netConnected(bool isConnected);
		void netRecvData(QByteArray array);

	private slots:
		void respRectNetData(QByteArray array);

	private:
		NetConnector(QObject *parent = nullptr);
		void initNetwork();

		void connectCallBack(Network::Uv_TcpClient * client);
		void closeCallBack(Network::Uv_TcpClient * client);
		void recvDataCallBack(Network::Uv_TcpClient * remoteClient, const char * data, int dataLen);

		bool searchNextPackHead();

		QByteArray makePacket(Datastruct::PacketType type,QByteArray & body);
		void sendData(const QByteArray & data);

	private:
		static NetConnector * m_instance;

		Network::Uv_EventLoop * m_eventLoop;		/*!< �¼�ѭ���߳� */
		Network::Uv_TcpClient * m_dataTcpClient;	/*!< ��ͨ�������� */

		Base::RFixedRingBuffer m_dataRecvRingBuffer;	/*!< ���ݽ��ջ��λ����� */
	};

} //namespace Related 