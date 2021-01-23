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
#include <base\common\sql\databasemanager.h>

namespace Related {

	class DataProcessCenter : public QObject
	{
		Q_OBJECT

	public:
		DataProcessCenter(QObject *parent = nullptr);
		~DataProcessCenter();
		
		/*! 
		 * @brief �����ݿ����ӡ�ÿ���̵߳����ݿ�����ֻ���ڵ�ǰ�߳���ʹ�á�
		 * @param db ���ݿ����Ӿ��
		 */
		void bindDatabase(Base::Database * db);

		Datastruct::UserLoginResponse processUserLogin(int clientId,const Datastruct::UserLoginRequest & request);

	private:
		Base::Database * m_database;

	};

} //