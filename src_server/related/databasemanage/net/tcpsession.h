/*!
 * @brief     TCP�ͻ�������
 * @details   ��װ���������ݵĽ�������͹��̣��ͻ����������Ӻ��ļ����ӿɼ̳д��࣬��ɶ�����Ĵ���
 * @author    wey
 * @version   1.0
 * @date      2021.01.30 14:42:08
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
 #pragma once

#include <QObject>

#include <base/util/rringbuffer.h>
#include <commondefines/protocol.h>
#include <network/libuv/uv_tcpserver.h>

namespace Related {

	class TcpSession
	{
	public:
		TcpSession(Network::AcceptTcpClient * client);
		~TcpSession();

		void sendData(const char * data, int dataLength);

		void recvData(const char * data, int dataLength);

	protected:
		/*! 
		 * @brief ����ȥ����ͷ��β�������������
		 * @details ���������Ҫ�ɶ���������в�ͬ�Ĵ���
		 * @param requestData �Ѿ������������������
		 */
		virtual void processData(QByteArray & requestData) = 0;

	private:
		bool searchNextPackHead();

	protected:
		Network::AcceptTcpClient * m_tcpClient;		/*!< �ͻ������� */
		Base::RFixedRingBuffer m_recvRingBuffer;	/*!< �ͻ��˶�Ӧ�Ľ��ջ��λ����� */
	};

} //namespace Related 