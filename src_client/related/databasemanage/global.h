#pragma once

#include <QObject>

#include <commondefines\protocol.h>
#include <commondefines\structdefines.h>

namespace Related {

	namespace Global {

		extern Datastruct::UserEntityData G_UserEntity;			/*!< ��ǰ��¼���û� */

		extern bool G_HasPrivilege(Datastruct::UserPrivilege up);	/*!< �鿴�����Ƿ����ĳ��Ȩ�� */

	}	//namespace Global {

} //namespace Related 
