/*!
 * @brief     ���ͨ�����ݽṹ
 * @author    wey
 * @version   1.0
 * @date      2021.01.09 16:32:24
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
#pragma once

#include <QString>

namespace Base {

	/*!
	 * @brief ����гߴ����ģʽ
	 */
	enum ColumnResizeMode {
		Interactive,		/*!< �ṩ�û�������ʽ��������ק�� */
		Fixed,				/*!< �й̶�ģʽ����resizeSection�ı��С */
		Strech,				/*!< ���Զ����������ɱ���ı��С */
		ResizeToContents	/*!< �Զ��ı������ݿ�ȣ����ɱ�����û���ק�ı��С */
	};

	/*!
	* @brief �Զ���������ʾ��
	* @details
	*/
	struct ColumnItem
	{
		ColumnItem() :ColumnItem(0, "", true, Qt::AlignCenter, Interactive, 120) {}
		ColumnItem(int id, QString name, bool visible = true, Qt::Alignment align = Qt::AlignCenter, ColumnResizeMode  model = Interactive, int width = 120) :m_id(id), m_name(name), m_visible(visible), m_align(align), m_columnWidth(width){}
		ColumnItem(int id, QString name, int width):ColumnItem(id,name,true,Qt::AlignCenter,Interactive,width){}

		int m_id;			/*!< ��Ψһ��ʶ */
		QString m_name;		/*!< ������ */
		bool m_visible;		/*!< ���Ƿ���ʾ */
		Qt::Alignment m_align;	/*!< �ж��뷽ʽ */

		ColumnResizeMode m_resizeModel;		/*!< ����иı�ģʽ */
		int m_columnWidth;					/*!< ����п�� */
	};

	typedef QList<ColumnItem> ColumnItems;

} //namespace Base 