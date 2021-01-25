/*!
 * @brief     �Զ��峣�ú�   
 * @author    wey
 * @version   1.0
 * @date      2021.01.25 14:19:37
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
#pragma once

#include <QObject>

/*!
 * @brief ��Ԫʵ�ֶ��ö��ֵ��λ�߼�����
 * @attention �����Ѿ��Ե�ǰö�ٵ���Q_DECLARE_FLAGS()��
 * @details Qt���Q_DECLARE_OPERATORS_FOR_FLAGS �겻���������ڵ�ö�ٶ����壬��Ϊ��չ����ʹ��2�������������롣���޸ĵ�ʱ��
			��ʹ����Ԫ��ʽ�����˺���д��
 */
#define Q_DECLARE_FRIEND_FLAGS(Flags) \
Q_DECL_CONSTEXPR inline friend QFlags<Flags::enum_type> operator|(Flags::enum_type f1, Flags::enum_type f2) Q_DECL_NOTHROW \
{ return QFlags<Flags::enum_type>(f1) | f2; } 