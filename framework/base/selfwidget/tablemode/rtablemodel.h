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

	typedef std::function<bool(const QVariant & va, const QVariant & vb)> CustomSortCallback;

	class BASESHARED_EXPORT RTableModel : public QAbstractTableModel
	{
		Q_OBJECT

	public:
		RTableModel(QObject *parent = nullptr);
		~RTableModel();

		virtual int rowCount(const QModelIndex &parent = QModelIndex() ) const;
		virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

		virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
		virtual QVariant headerData(int section, Qt::Orientation orientation, int role /* = Qt::DisplayRole */) const;

		int getPageNum() const { return m_pageNum; }

		/*!
		 * @brief �������µ�ǰ���������
		 * @param items ����������
		 */
		void updateColumnItems(ColumnItems items);
		QList<ColumnItem> getColumns() { return m_columns; }

		void setColumVisible(int id,bool visible);
		int visibleColumnCount();
		
		/*!
		 * @brief �Ե�ǰ��ʾ���ݣ�ָ��������
		 * @param column ��������б��
		 * @param ord ����˳��
		 */
		void sortByColumn(int column, Qt::SortOrder ord);

		/*!
		 * @brief Ϊָ���������������
		 * @param columnId �����ûص���������
		 * @param callback �Զ����������
		 */
		void addCustomColumSortStragety(int columnId, CustomSortCallback callback);

		/*!
		 * @brief ˢ�±������
		 * @details 1.�����������״̬������������
					2.ˢ�±����ʾ
		 */
		void refresh();

	public slots:
		/*!
		 * @brief ���ñ��̶���ʾ����
		 * @note �����ù̶���ʾ�У����������踲дrowCount()������
		 * @param rowNums �����õĹ̶��У��������0
		 */
		void setFixedPageRowCount(int rowNums);

		/*!
		 * @brief ���õ�ǰҳ������
		 * @attention ֻ�н�������Ҫ��ʾ������һ����������model�У��ſ������ô˹���
		 * @param page ҳ��������ţ���0��ʼ��
		 */
		void setPageNum(int page);

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

		/*!
		 * @brief ����ִ������Ĵ���
		 */
		void executeSort();

		ColumnItem getVisibleItem(int index) const;

	protected:
		ColumnItems m_columns;

		int m_itemsPerPage;		/*!< ��ǰҳ����ʾ���� >0 ��ʾÿҳ������ʾ������<0��ʾ������ */
		int m_pageNum;		    /*!< ��ǰҳ������0��ʼ */
		int m_perPageCount;		/*!< ÿҳ�̶����� */

		QList<int> m_sortedRows;	/*!< �����������������ÿ�����ݶ�Ӧ����� */
		int m_sortedColumn;			/*!< ��ǰ������������>= 0��ʾ������Ч */
		Qt::SortOrder m_sortOrder;	/*!< ��ǰ�������˳�� */
		QMap<int, CustomSortCallback> m_sortCallback;		/*!< ָ����������ԣ�����ǰ��û�����ã���ʹ��Ĭ��������� */
	};

} //namespace Base 