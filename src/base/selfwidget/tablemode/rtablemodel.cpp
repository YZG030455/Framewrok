#include "rtablemodel.h"

#include <QDebug>
#include <QDate>
#include <QTime>
#include <QDateTime>

namespace Base {

	struct SortUnit
	{
		SortUnit():m_row(0){}
		SortUnit(int row, QVariant data) :m_row(row), m_data(data) {}

		int m_row;		/*!< ���ݶ����У���ǰ�������(��һ����������״̬) */
		QVariant m_data;
	};

	class MySortOrder {
	public:
		MySortOrder():m_ascending(false){}
		MySortOrder(bool ascendingOrder):m_ascending(ascendingOrder){}

		bool operator()(SortUnit va, SortUnit vb) {
			QVariant left = va.m_data;
			QVariant right = vb.m_data;

			bool isLessThan = false;

			switch (left.userType()) {
			case QVariant::Invalid:
				isLessThan = (right.type() != QVariant::Invalid);
				break;
			case QVariant::Int:
				isLessThan = left.toInt() < right.toInt();
				break;
			case QVariant::UInt:
				isLessThan = left.toUInt() < right.toUInt();
				break;
			case QVariant::LongLong:
				isLessThan = left.toLongLong() < right.toLongLong();
				break;
			case QVariant::ULongLong:
				isLessThan = left.toULongLong() < right.toULongLong();
				break;
			case QMetaType::Float:
				isLessThan = left.toFloat() < right.toFloat();
				break;
			case QVariant::Double:
				isLessThan = left.toDouble() < right.toDouble();
				break;
			case QVariant::Char:
				isLessThan = left.toChar() < right.toChar();
				break;
			case QVariant::Date:
				isLessThan = left.toDate() < right.toDate();
				break;
			case QVariant::Time:
				isLessThan = left.toTime() < right.toTime();
				break;
			case QVariant::DateTime:
				isLessThan = left.toDateTime() < right.toDateTime();
				break;
			case QVariant::String:
			default:
				isLessThan = left.toString().localeAwareCompare(right.toString()) < 0;
				break;
			}

			return m_ascending ? isLessThan : !isLessThan;
		}

	private:
		bool m_ascending;
	};

	RTableModel::RTableModel(QObject *parent)
		: QAbstractTableModel(parent), m_sortedColumn(-1), m_sortOrder(Qt::AscendingOrder), m_perPageCount(30),m_pageNum(0)
	{

	}

	RTableModel::~RTableModel()
	{
	}

	int RTableModel::rowCount(const QModelIndex &parent /* = QModelIndex() */) const
	{
		return m_perPageCount;
	}

	int RTableModel::columnCount(const QModelIndex &parent /*= QModelIndex()*/) const
	{
		int visibleCount = std::count_if(m_columns.begin(), m_columns.end(), [](const ColumnItem & item) {
			return item.m_visible;
		});

		return visibleCount;
	}

	QVariant RTableModel::data(const QModelIndex &index, int role /*= Qt::DisplayRole*/) const
	{
		if (!index.isValid() || index.column() > m_columns.size())
			return QVariant();

		ColumnItem && item = getVisibleItem(index.column());

		if (role == Qt::DisplayRole) {
			//��ǰҳ�棬��һ�����ݵ���ʼ����.�Ѵ�ֵ�������ݵ���ʼƫ��
			int dataStartIndex = m_pageNum * rowCount();
			if(!m_sortedRows.isEmpty() && m_sortedRows.size() > index.row())
				return displayData(index.row(), dataStartIndex + m_sortedRows.at(index.row()),item.m_id);
			else {
				return displayData(index.row(), dataStartIndex + index.row(), item.m_id);
			}
		}
		else if (role == Qt::TextAlignmentRole) {
			return item.m_align;
		}

		return customProcessRole(role, index.row(), 0, item.m_id);
	}

	QVariant RTableModel::headerData(int section, Qt::Orientation orientation, int role /* = Qt::DisplayRole */) const
	{
		if (section > m_columns.size())
			return QVariant();

		ColumnItem && item = getVisibleItem(section);

		if (orientation == Qt::Horizontal) {
			if (role == Qt::DisplayRole) {
				return item.m_name;
			}
			else if (role == Qt::TextAlignmentRole) {
				return item.m_align;
			}
		}

		return QVariant();
	}

	void RTableModel::setFixedPageRowCount(int rowNums)
	{
		if (rowNums > 0) {
			m_perPageCount = rowNums;
			refresh();
		}
	}

	void RTableModel::setPageNum(int page)
	{
		if (page >= 0)
			m_pageNum = page;
	}

	void RTableModel::updateColumnItems(ColumnItems items)
	{
		beginResetModel();
		m_columns.swap(items);
		endResetModel();
	}

	void RTableModel::setColumVisible(int id, bool visible)
	{
		for (int i = 0; i < m_columns.size(); i++) {
			if (m_columns[i].m_id == id) {
				m_columns[i].m_visible = visible;
				break;
			}
		}
	}

	int RTableModel::visibleColumnCount()
	{
		return std::count_if(m_columns.begin(), m_columns.end(), [](const ColumnItem & item) {
			return item.m_visible;
		});
	}

	/*!
	* @brief ��ָ��������
	* @details 1.����ǰ����ȡÿ��ԭʼ�����ݺͶ�Ӧ��˳�򣬰�װ��һ������Ԫ������������б�
			   2.����ʱ���������б�������򣬱Ƚ�����Ԫ�ڵ�ԭʼ���ݣ����������ı䵥������Ԫ�ڼ����е�λ�ã�
			   3.���������ˢ��ʱ��ͨ���кŻ�ȡ����������Ԫ����ͨ����Ӧ��˳��ֵ����ԭʼ�����б��ȡȡ������ʾ���ɡ�
	* @param column ��������б��
	* @param ord ����˳��
	*/
	void RTableModel::sortByColumn(int column, Qt::SortOrder ord)
	{
		m_sortedColumn = column;
		m_sortOrder = ord;

		executeSort();
	}

	void RTableModel::addCustomColumSortStragety(int columnId, CustomSortCallback callback)
	{
		m_sortCallback.insert(columnId, callback);
	}

	void RTableModel::refresh()
	{
		if (m_sortedColumn >= 0)
			executeSort();

		beginResetModel();
		endResetModel();
	}

	QVariant RTableModel::displayData(int rowIndex, int dataIndex, int columnId) const
	{
		return QVariant();
	}

	QVariant RTableModel::customProcessRole(int role, int rowIndex, int dataIndex, int columnId) const
	{
		return QVariant();
	}

	void RTableModel::executeSort()
	{
		//[1]
		int dataStartIndex = m_pageNum * rowCount();

		QList<SortUnit> dataList;
		for (int i = 0; i < rowCount(); i++) {
			//��ȡԭʼ���ݣ���������������
			QVariant vdata = displayData(i, dataStartIndex +  i, m_sortedColumn);
			if (!vdata.isNull()) {
				dataList << SortUnit(i, vdata);
			}
		}

		//[2]
		Base::ColumnItem citem = getVisibleItem(m_sortedColumn);
		if (m_sortCallback.contains(citem.m_id)) {
			std::stable_sort(dataList.begin(), dataList.end(), [&](const SortUnit & sa, const SortUnit & sb) {
				return m_sortCallback.value(citem.m_id)(sa.m_data, sb.m_data);
			});
		}
		else {
			MySortOrder st(m_sortOrder == Qt::AscendingOrder);
			std::stable_sort(dataList.begin(), dataList.end(), st);
		}

		//[3]
		m_sortedRows.clear();
		for (SortUnit & st : dataList)
			m_sortedRows << st.m_row;
	}

	Base::ColumnItem RTableModel::getVisibleItem(int index) const
	{
		int loop = 0;
		for (int i = 0; i < m_columns.size(); i++) {
			if (m_columns[i].m_visible) {
				if (loop++ == index)
					return m_columns[i];
			}
		}
	}

} //namespace Base 