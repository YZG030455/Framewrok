/*!
 * @brief     �ͻ��˺ͷ�������ͨ������Э��
 * @attention 1.ÿ��Э��˵�������˭���͡�˭���գ�
			  2.���ɿͻ��˷���������������ͳһ��Request��β��
			  3.���ɷ��������ؿͻ��ˣ���ͳһ��Response��β��
 * @author    wey
 * @version   1.0
 * @date      2021.01.20 15:45:05
 * @warning	  �ͻ��˺ͷ������˵İ汾����һ��
 * @copyright NanJing RenGu.
 * @note
 */
#pragma once

#include <qglobal.h>
#include <QString>

namespace Related {

#pragma pack(push,1)

#define PACK_HEAD 0xAABB7788		/*!< ����ͷͷ��ʶ */
#define PACK_TAIL 0x8877BBAA		/*!< ����β��ʶ */

	/*!
	 * @brief ͨѶ���ݰ���������
	 * @details �ͻ��˺ͷ�������ͨ�������ͽ���ʶ�����ݰ���ȷ������ͳһ
	 */
	enum PacketType {
		P_UserLogin = 1,		/*!< �û���¼ */
		P_UserRegist,			/*!< �û�ע�� */
		P_UserList,				/*!< �û��б��ѯ */
		P_UserUpdate,			/*!< �û���Ϣ����,����Ȩ�޸��� */
		P_UserDelete,			/*!< ɾ���û� */

		P_CreateTask = 10,		/*!< �������� */
		P_TaskList,				/*!< ��ѯ�������� */
		P_TaskByCondition,		/*!< ��������ѯ���� */
		P_TaskDelete,			/*!< ɾ������ */
		P_TaskStaticsInfo,		/*!< ����ͳ����Ϣ��������������ռ�ÿռ��С�� */
		P_TaskSimpleInfo,		/*!< �������������Ϣ */
		P_TaskFullInfo			/*!< ����������ϸ��Ϣ */
	};

	/*!
	 * @brief ͨѶ����Э��ͷ
	 * @details ���ڱ�ʶ���ݰ����ͣ��ж����ݰ��߽�
	 */
	struct PacketHead {
		PacketHead() :m_magicHead(PACK_HEAD), m_dataLen(0), m_packetType(0) {}
		uint m_magicHead;		/*!< ����ͷ��ʶ */
		uint m_dataLen;			/*!< ��������ͷ��������������β���� */
		ushort m_packetType;	/*!< ָ������ */
	};

	struct PacketTail
	{
		PacketTail() :m_magicTail(PACK_TAIL) {}
		uint m_magicTail;		/*!< ����β��ʶ */
	};

#pragma  pack(pop)

	/*!
	 * @brief �û���¼����
	 * @details �ͻ���->��������
	 */
	struct UserLoginRequest {
		QString m_name;			/*!< �û��� */
		QString m_password;		/*!< ���룬ת����MD5 */
	};

	/*!
	 * @brief �û���¼�������
	 * @details ��������->�ͻ���
	 */
	struct UserLoginResponse {
		bool m_loginResult;		/*!< ��¼�����Ϣ��true:��¼�ɹ���false:��¼ʧ�� */
		QString m_errorInfo;	/*!< ��¼ʧ��ʱ˵��ʧ��ԭ�� */
	};

} //namespace Related 
