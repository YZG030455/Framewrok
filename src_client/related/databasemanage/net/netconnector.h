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

#include <base\util\rringbuffer.h>
#include <network\libuv\uv_eventloop.h>
#include <network\libuv\uv_tcpclient.h>

#include "protocol.h"

namespace Related {

	class NetConnector : public QObject
	{
		Q_OBJECT
	public:
		static NetConnector * instance();
		~NetConnector();

		/*! 
		 * @brief ������ָ����ip�Ͷ˿ںŷ�������
		 * @attention ���ô˷�������Ҫ�ȴ�����netConnected�źţ����ж϶�Ӧ�Ĳ������ſ���ȷ�������Ƿ����ӳɹ�
		 * @param remoteIp Զ�̷�����IP
		 * @param remotePort Զ�̷������˿ں�
		 */
		void connectTo(QString remoteIp,ushort remotePort);

		/*! 
		 * @brief ������������������Ƿ���
		 * @return true:�ѽ����������ӣ�false:δ������������
		 */
		bool isConnected();

		void write(PacketType type,const UserLoginRequest & request);

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

		QByteArray makePacket(PacketType type,QByteArray & body);

	private:
		static NetConnector * m_instance;

		Network::Uv_EventLoop * m_eventLoop;		/*!< �¼�ѭ���߳� */
		Network::Uv_TcpClient * m_dataTcpClient;	/*!< ��ͨ�������� */

		Base::RFixedRingBuffer m_dataRecvRingBuffer;	/*!< ���ݽ��ջ��λ����� */
	};

} //namespace Related 