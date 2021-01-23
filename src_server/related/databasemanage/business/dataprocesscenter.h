/*!
 * @brief     ���������������ҵ�񣬲�����ִ�н��   
 * @author    wey
 * @version   1.0
 * @date      2021.01.23 10:06:22
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
 #pragma once

#include <QObject>

#include <commondefines/protocol.h>

namespace Related {

	class DataProcessCenter : public QObject
	{
		Q_OBJECT

	public:
		DataProcessCenter(QObject *parent = nullptr);
		~DataProcessCenter();

		Datastruct::UserLoginResponse processUserLogin(int clientId,const Datastruct::UserLoginRequest & request);

	};

} //