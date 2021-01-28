#pragma once

#include <QObject>

#include <commondefines\protocol.h>
#include <commondefines\structdefines.h>
#include <base\util\widgetanimation.h>

namespace Related {

	namespace Global {

		extern Datastruct::UserEntityData G_UserEntity;			/*!< ��ǰ��¼���û� */

		extern bool G_HasPrivilege(Datastruct::UserPrivilege up);	/*!< �鿴�����Ƿ����ĳ��Ȩ�� */

		extern Base::WidgetAnimation G_WidgetAnimation;			/*!< ȫ�ֿؼ��������� */

	}	//namespace Global {

} //namespace Related 
