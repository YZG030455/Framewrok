#include "targetdatabasemanagepage.h"

#include <QDebug>

#include "../../utils/util.h"
#include "../../customwidget/customwidgetcontainer.h"

namespace Related {

	TargetDatabaseManagePage::TargetDatabaseManagePage(QWidget *parent)
		: QWidget(parent)
	{
		init();
		initConnect();
	}

	TargetDatabaseManagePage::~TargetDatabaseManagePage()
	{
	}

	void TargetDatabaseManagePage::respToolButtPressed(OperationToolsPage::ButtType type)
	{
		switch (type)
		{
		case OperationToolsPage::Butt_Add: {

		}
			break;
		case OperationToolsPage::Butt_Delete: {

		}
			break;
		case OperationToolsPage::Butt_Edit: {

		}
			break;
		case OperationToolsPage::Butt_Refresh: {

		}
			break;
		default:
			break;
		}
	}

	void TargetDatabaseManagePage::setPageNum(int page)
	{
	}

	void TargetDatabaseManagePage::setFixedPageRowCount(int pageItemCount)
	{
		m_tableModel->setFixedPageRowCount(pageItemCount);
	}

	void TargetDatabaseManagePage::init()
	{
		CustomWidgetContainer * cwidget = new CustomWidgetContainer();
		{
			m_operationToolsPage = new OperationToolsPage();	
			connect(m_operationToolsPage, SIGNAL(buttPressed(OperationToolsPage::ButtType)), 
				this, SLOT(respToolButtPressed(OperationToolsPage::ButtType)));
			cwidget->setContent(m_operationToolsPage);
		}

		CustomWidgetContainer * ctableView = new CustomWidgetContainer();
		{
			m_tableView = new Base::RTableView();
			m_tableView->setFocusPolicy(Qt::NoFocus);
			m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
			m_tableView->setSelectionMode(QAbstractItemView::SingleSelection);

			m_tableModel = new TargetDatabaseManageModel();
			m_tableModel->prepareData();

			m_tableView->setModel(m_tableModel);

			m_tableView->addColumnItem(Base::ColumnItem(T_Index, QStringLiteral("����")));
			m_tableView->addColumnItem(Base::ColumnItem(T_TargetName, QStringLiteral("Ŀ������"), 140));
			m_tableView->addColumnItem(Base::ColumnItem(T_Edttime, QStringLiteral("¼��ʱ��"), 180));
			m_tableView->addColumnItem(Base::ColumnItem(T_Tonnage, QStringLiteral("��λ(t)"), 180));
			m_tableView->addColumnItem(Base::ColumnItem(T_Lon, QStringLiteral("����"), 180));
			m_tableView->addColumnItem(Base::ColumnItem(T_Lat, QStringLiteral("γ��"), 180));
			m_tableView->addColumnItem(Base::ColumnItem(T_Speed, QStringLiteral("�����ٶ�"), 180));
			m_tableView->addColumnItem(Base::ColumnItem(T_AxlesNumber, QStringLiteral("����")));
			m_tableView->addColumnItem(Base::ColumnItem(T_Type, QStringLiteral("����")));

			m_pageSwitch = new PageSwitchBar();
			m_pageSwitch->setDataSize(m_tableModel->datasSize());
			connect(m_pageSwitch, SIGNAL(perPageNumsChanged(int)), this, SLOT(setFixedPageRowCount(int)));
			connect(m_pageSwitch, SIGNAL(switchPage(int)), this, SLOT(setPageNum(int)));

			QWidget * twidget = new QWidget();
			QVBoxLayout * cvlayout = new QVBoxLayout();
			cvlayout->setContentsMargins(0, 0, 0, 0);
			cvlayout->addWidget(m_tableView);
			cvlayout->addWidget(m_pageSwitch);
			twidget->setLayout(cvlayout);

			ctableView->setContent(twidget);
		}

		QVBoxLayout * vlayout = new QVBoxLayout();
		vlayout->setContentsMargins(4, 4, 4, 4);
		vlayout->addWidget(cwidget);
		vlayout->addWidget(ctableView);
		setLayout(vlayout);
	}

	void TargetDatabaseManagePage::initConnect()
	{

	}

}//namespace Related 
