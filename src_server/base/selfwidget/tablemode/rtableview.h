/*!
 * @brief     �Զ�������ͼ
 * @details   1.֧�ֱ�����ֶ�����
			  2.֧��������
			  3.֧�ּ�¼��ǰ�п�ȣ�����������ʾ�󣬿�ȷ���еĿ����Ϣ����
 * @author    wey
 * @version   1.0
 * @date      2021.01.08 16:44:51
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
#pragma once

#include <QWidget>
#include <QTableView>
#include <QMenu>

#include "../../base_global.h"
#include "tablestruct.h"

namespace Base {

	class RTableModel;

	class BASESHARED_EXPORT RTableView : public QTableView
	{
		Q_OBJECT

	public:
		RTableView(QWidget *parent = nullptr);
		~RTableView();

		/*!
		 * @brief ���ñ������ģ��
		 * @attention 1.�˷����Ḳ��QTableView��ͬ��������ֻ�����Զ����ģ��
		 *			  2.ֻ���ȵ���setModel()�����ñ����п�Ż���Ч
		 * @param model �Զ�����ģ��
		 */
		void setModel(RTableModel *model);

		/*!
		 * @brief �������
		 */
		enum TableFeature {
			T_ColumnEdit = 0x0001,			/*!< ���༭(������������) */
			T_HeadSorting = 0x0002, 		/*!< ��ͷ���� */
			T_AlternatingRowColors = 0x0004	/*!< ���б�ɫ */
		};
		Q_DECLARE_FLAGS(TableFeatures, TableFeature);
		
		/*!
		 * @brief ���Ʊ�����Կ�����ر�
		 * @param feature �����Ƶı������
		 * @param enabled true:���ã�false:�ر�
		 */
		void setTableFeature(TableFeature feature,bool enabled);

		/*!
		 * @brief ��ӱ����
		 * @param item �������Ϣ����
		 * @return true:��ӳɹ���false:��ʾ�Ѿ�������ͬid��name����
		 */
		bool addColumnItem(ColumnItem item);

	private slots:
		void respCustomContextMenu(const QPoint & point);

		void showColumnVisibleEditWindow(bool flag);
		void updateModelColumnVisible(bool flag);

		/*!
		 * @brief ��ͷ�������
		 * @param column ����ı�ͷ�б��
		 */
		void respSectionClicked(int column);

		/*!
		 * @brief �������иı�
		 * @param logicalIndex �ı���������
		 * @param oldSize �ı�ǰ�п��/�߶�
		 * @param newSiz �ı���п��
		 */
		void respColumnResize(int logicalIndex, int oldSize, int newSiz);

	private:
		void udateFeature();
		void resizeColumnWidth();

	private:
		QMenu * m_headMenu;
		TableFeatures m_tableFeatures;
		int m_lastClickedColumn;
		bool m_ascending;		/*!< true������false������ */

		ColumnItems m_columns;	/*!< ���б���� */
		bool m_columResizeByUser;		/*!< �û��ֹ������п� */
	};

} //namespace Base 
