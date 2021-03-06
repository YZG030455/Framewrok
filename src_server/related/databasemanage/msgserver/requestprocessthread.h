#pragma once

#include <QObject>

#include <commondefines/protocol.h>
#include <base\common\sql\databasemanager.h>
#include <core/network/rtask.h>

#include "../datastruct.h"
#include "../business/dataprocesscenter.h"

namespace Related {

	struct RequestUnit;

	class RequestProcessThread : public Core::RTask
	{
		Q_OBJECT

	public:
		RequestProcessThread(QObject *parent = nullptr);
		~RequestProcessThread();

		void startMe();
		void stopMe();

	signals:
		void sendProcessResult(ResponseUnit * result);

	protected:
		void run();

	private:
		void parseRequest(RequestUnit * unit);
		QByteArray makePacket(Datastruct::PacketType type, const QByteArray & body);

	private:
		DataProcessCenter m_processCenter;		/*!< ҵ���� */

		Base::Database * m_dbConnect;
	};

} //namespace Related 