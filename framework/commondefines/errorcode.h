/*!
 * @brief     ������  
 * @author    wey
 * @version   1.0
 * @date      2021.01.25 17:23:55
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
 #pragma once

#include <QObject>

#include "commondefines_global.h"

namespace Datastruct {

	/*!
	 * @brief ���ݷ��ʡ����������д�����
	 * @details �ͻ��˺ͷ�������ͨ��ͳһ��Լ��������Ӳ����
	 */
	enum ErrorCode {
		//ҵ�����
		PASSWROD_ERROR = 1,
		NO_REGIST,
		USER_EXIST,
		NO_USER,
		NO_PRIVILEGE,


		//���ݿ�������
		SQL_EXECUTE_ERROR = 100,
	};

	/*! 
	 * @brief ��ѯ�������Ӧ��������Ϣ
	 * @param code ������
	 * @return ������Ϣ
	 */
	extern COMMONDEFINESHARED_EXPORT QString G_StrError(ErrorCode code);		/*!< ��ȡ��Ӧ������������Ϣ */

}	//namespace Datastruct 
