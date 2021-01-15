#include "candidatedatapage.h"

#include <QVBoxLayout>
#include "../customwidget/pageswitchbar.h"

namespace Related {

	CandidateDataPage::CandidateDataPage(QWidget *parent)
		: QWidget(parent)
	{
		init();
	}

	CandidateDataPage::~CandidateDataPage()
	{

	}

	void CandidateDataPage::init()
	{
		m_tableView = new Base::RTableView();
		m_tableView->setFocusPolicy(Qt::NoFocus);
		m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
		m_tableView->setSelectionMode(QAbstractItemView::SingleSelection);
		m_tableView->addColumnItem(Base::ColumnItem(D_Id, QStringLiteral("���")));
		m_tableView->addColumnItem(Base::ColumnItem(D_BatchNumber, QStringLiteral("����")));
		m_tableView->addColumnItem(Base::ColumnItem(D_Time, QStringLiteral("ʱ��")));
		m_tableView->addColumnItem(Base::ColumnItem(D_LocalDistinguish, QStringLiteral("ʶ����")));
		m_tableView->addColumnItem(Base::ColumnItem(D_Result, QStringLiteral("���Ŷ�")));
		m_tableView->addColumnItem(Base::ColumnItem(D_PlatformName, QStringLiteral("�϶�״̬")));

		m_tableModel = new CandidateDataModel();
		m_tableModel->prepareData();
		m_tableView->setModel(m_tableModel);

		PageSwitchBar * pageSwitch = new PageSwitchBar();
		connect(pageSwitch, SIGNAL(perPageNumsChanged(int)), m_tableModel, SLOT(setFixedPageRowCount(int)));

		QVBoxLayout * tableLayout = new QVBoxLayout();
		tableLayout->addWidget(m_tableView);
		tableLayout->addWidget(pageSwitch);
		tableLayout->setContentsMargins(4, 4, 4, 4);

		setLayout(tableLayout);
	}

}//namespace Related 