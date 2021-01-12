/*!
 * @brief     ͨ�ñ��ģ��
 * @details	  1.֧�ֶ�̬�еĵ�����������˳�����
			  2.�ṩ���ٽ������������ʾ������
 * @author    wey
 * @version   1.0
 * @date      2021.01.08 16:36:43
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
#pragma once

#include <QObject>
#include <QAbstractTableModel>
#include <QList>

#include "../../base_global.h"
#include "tablestruct.h"

namespace Base {

	class BASESHARED_EXPORT RTableModel : public QAbstractTableModel
	{
		Q_OBJECT

	public:
		RTableModel(QObject *parent = nullptr);
		~RTableModel();

		virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

		virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
		virtual QVariant headerData(int section, Qt::Orientation orientation, int role /* = Qt::DisplayRole */) const;

		/*!
		 * @brief �������µ�ǰ���������
		 * @param items ����������
		 */
		void updateColumnItems(ColumnItems items);
		QList<ColumnItem> getColumns() { return m_columns; }

		void setColumVisible(int id,bool visible);
		int visibleColumnCount();

		void refresh();

		/*!
		 * @brief ����ҳ��������ʾ����
		 * @param nums >0 ��ʾÿҳ������ʾ������<0��ʾ������
		 */
		void setPageItemCount(int nums);

	protected:
		/*!
		 * @brief ��ȡָ���С��е���ʾ����
		 * @param rowIndex ��ǰ�к�
		 * @param dataIndex �������������ݼ����е�����
		 * @param columnId �б�ʶ����ͨ���˱�ʶ������
		 * @return ��Ԫ����ʾ����
		 */
		virtual QVariant displayData(int rowIndex,int dataIndex,int columnId) const;

		/*!
		 * @brief �Զ��崦��Ԫ������
		 * @param rowIndex ��ǰ�к�
		 * @param dataIndex �������������ݼ����е�����
		 * @param columnId �б�ʶ����ͨ���˱�ʶ������
		 * @return ��Ԫ����ʾ����
		 */
		virtual QVariant customProcessRole(int role, int rowIndex, int dataIndex, int columnId) const;

		ColumnItem getVisibleItem(int index) const;

	protected:
		ColumnItems m_columns;

		int m_itemsPerPage;		/*!< ��ǰҳ����ʾ���� >0 ��ʾÿҳ������ʾ������<0��ʾ������ */
		int m_pageCount;		/*!< ��ǰҳ������0��ʼ */
	};


} //namespace Base 