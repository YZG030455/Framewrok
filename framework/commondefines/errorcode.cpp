#include "errorcode.h"

namespace Datastruct {

	extern QString G_StrError(ErrorCode code)
	{
		switch (code)
		{
			case Datastruct::PASSWROD_ERROR:
				return QStringLiteral("�˻��������!");
				break;
			case Datastruct::NO_REGIST:
				return QStringLiteral("�˻�δע��!");
				break;
			case Datastruct::USER_EXIST:
				return QStringLiteral("�û����Ѵ���!");
				break;
			case Datastruct::NO_USER:
				return QStringLiteral("δ�ҵ�ָ���û�!");
				break;
			case Datastruct::NO_PRIVILEGE:
				return QStringLiteral("�޲���Ȩ��!");
				break;




			case Datastruct::SQL_EXECUTE_ERROR:
				return QStringLiteral("���ݷ���ʧ��!");
				break;
			default:
				break;
		}

		return QStringLiteral("δ֪����");
	}

}	//namespace Datastruct 
