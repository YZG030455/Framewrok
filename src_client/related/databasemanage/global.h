#pragma once

#include <QObject>

#include <commondefines\protocol.h>
#include <commondefines\structdefines.h>
#include <base\util\widgetanimation.h>

#include "customwidget\loadingdialog.h"

namespace Related {

	namespace Global {

		extern Datastruct::UserEntityData G_UserEntity;			/*!< ��ǰ��¼���û� */
		extern LoadingDialog * G_LoadingDialog;					/*!< �ȴ����� */

		extern bool G_HasPrivilege(Datastruct::UserPrivilege up);	/*!< �鿴�����Ƿ����ĳ��Ȩ�� */

		extern Base::WidgetAnimation G_WidgetAnimation;			/*!< ȫ�ֿؼ��������� */

	}	//namespace Global 


	#define START_WAIT Global::G_LoadingDialog->showMe();
	#define START_WAIT_ON(parent) Global::G_LoadingDialog->showMe(parent);

	#define END_WAIT Global::G_LoadingDialog->hideMe();

} //namespace Related 
