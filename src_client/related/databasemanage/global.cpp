#include "global.h"

namespace Related {

	namespace Global {

		Datastruct::UserEntityData G_UserEntity;			/*!< ��ǰ��¼���û� */

		/*! 
		 * @brief ��⵱ǰ��¼�û��Ƿ����ĳЩȨ��
		 * @param up ������Ȩ��
		 * @return true:�߱�ָ��Ȩ��;false:���߱�ָ��Ȩ��
		 */
		bool G_HasPrivilege(Datastruct::UserPrivilege up) {
			return G_UserEntity.privilege & up;
		}

	} //namespace Global 

} //namespace Related 