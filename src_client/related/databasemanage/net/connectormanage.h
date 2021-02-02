/*!
 * @brief     �������ӹ�������ά�����ݡ��ļ��������ӵ�װ������ֶ��������Զ�����
 * @author    wey
 * @version   1.0
 * @date      2021.02.02 08:49:51
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
#pragma once

#include <QObject>

#include <commondefines/structdefines.h>

namespace Related {

	class ConnectorManage : public QObject
	{
		Q_OBJECT

	public:
		static ConnectorManage * instance();
		~ConnectorManage();

		enum NetConnectedFlag
		{
			DataConnected = 0x0001,		/*!< ������·������ */
			FileConnected = 0x0002,		/*!< �ļ���·������ */
			AllConnected = DataConnected | FileConnected
		};
		Q_DECLARE_FLAGS(NetConnectedState, NetConnectedFlag)

		bool allNetConnected() const { return m_netState == AllConnected; }
		void startConnect(QString serverIp, ushort dataPort, ushort filePort);

		void setNetAutoConnect(bool isReconn,int maxReconnTimes);

	signals:
		void connectResult(Datastruct::ConnectionType type, bool connected, QString errorInfo = "");
		void reconnResult(Datastruct::ConnectionType type, int times);

	private slots:
		void respNetConnected(Datastruct::ConnectionType ctype, bool connected);
		void respReConnTimes(Datastruct::ConnectionType ctype, int times);

	private:
		ConnectorManage();

	private:
		static ConnectorManage * m_instance;

		NetConnectedState m_netState;
		bool m_isNetConnecting;		/*!< ��·�Ƿ��������� */
	};

} //namespace Related 