#include "connectormanage.h"

#include "datanetconnector.h"
#include "filenetconnector.h"

namespace Related {

	ConnectorManage * ConnectorManage::m_instance = nullptr;

	ConnectorManage::ConnectorManage()
		: QObject()
	{

		connect(DataNetConnector::instance(), SIGNAL(netConnected(Datastruct::ConnectionType, bool)), this, SLOT(respNetConnected(Datastruct::ConnectionType, bool)));
		connect(FileNetConnector::instance(), SIGNAL(netConnected(Datastruct::ConnectionType, bool)), this, SLOT(respNetConnected(Datastruct::ConnectionType, bool)));

		//NOTE Ĭ���ṩ�Զ��������ƣ��û�Ҳ�����ֶ�����
		DataNetConnector::instance()->setAutoReconnect(true);
		FileNetConnector::instance()->setAutoReconnect(true);
	}

	ConnectorManage * ConnectorManage::instance()
	{
		if (m_instance == nullptr)
			m_instance = new ConnectorManage();

		return m_instance;
	}

	ConnectorManage::~ConnectorManage()
	{
	}

	void ConnectorManage::startConnect(QString serverIp, ushort dataPort, ushort filePort)
	{
		if (!DataNetConnector::instance()->isConnected()) {
			if (DataNetConnector::instance()->connectTo(serverIp, dataPort)) {

			}
			else {
				emit connectResult(Datastruct::Data_Connection,false, QStringLiteral("�������ݷ�����ʧ��!"));
			}
		}
		else {
			emit(Datastruct::Data_Connection,true);
		}

		if (!FileNetConnector::instance()->isConnected()) {
			if (FileNetConnector::instance()->connectTo(serverIp, filePort)) {

			}
			else {
				emit connectResult(Datastruct::Data_Connection, false, QStringLiteral("�����ļ�������ʧ��!"));
			}
		}
		else {
			emit(Datastruct::File_Connection, true);
		}
	}

	void ConnectorManage::respNetConnected(Datastruct::ConnectionType ctype, bool connected)
	{
		if (connected) {
			emit connectResult(ctype, true);
		}
		else {
			if (ctype == Datastruct::Data_Connection) {
				emit connectResult(Datastruct::Data_Connection, false, QStringLiteral("�������ݷ�����ʧ��!"));
			}
			else {
				emit connectResult(Datastruct::Data_Connection, false, QStringLiteral("�����ļ�������ʧ��!"));
			}
		}
	}

} //namespace Related 