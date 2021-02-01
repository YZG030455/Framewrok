#include "aisdatapage.h"

#include <QDebug>

#include "../../utils/util.h"
#include "../../customwidget/customwidgetcontainer.h"
#include "../../net/datanetconnector.h"
#include "../../net/signaldispatch.h"
#include "../../global.h"

namespace Related {

	AisDataPage::AisDataPage(QWidget *parent)
		: AbstractPage(parent),
		m_firstLoadData(false)
	{
		init();
		initConnect();
		createData();
	}

	AisDataPage::~AisDataPage()
	{
	}

	PageType AisDataPage::getPageType() const
	{
		return Page_AisDataBase_AisData;
	}

	void AisDataPage::respToolButtPressed(OperationToolsPage::ButtType type)
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

	void AisDataPage::setPageNum(int page)
	{
	}

	void AisDataPage::setFixedPageRowCount(int pageItemCount)
	{
		m_tableModel->setFixedPageRowCount(pageItemCount);
	}

	void AisDataPage::init()
	{
		CustomWidgetContainer * cwidget = new CustomWidgetContainer();
		{
			m_operationToolsPage = new OperationToolsPage();
			connect(m_operationToolsPage, SIGNAL(buttPressed(OperationToolsPage::ButtType)), this, SLOT(respToolButtPressed(OperationToolsPage::ButtType)));
			cwidget->setContent(m_operationToolsPage);
		}

		CustomWidgetContainer * ctableView = new CustomWidgetContainer();
		{
			m_tableModel = new AisDataModel();

			m_tableView = new Base::RTableView();
			m_tableView->setFocusPolicy(Qt::NoFocus);
			m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
			m_tableView->setSelectionMode(QAbstractItemView::SingleSelection);

			m_tableView->setModel(m_tableModel);
			m_tableView->addColumnItem(Base::ColumnItem(AIS_Index, QStringLiteral("����")));
			m_tableView->addColumnItem(Base::ColumnItem(AIS_Mmsi, QStringLiteral("����MMSI"), 180));
			m_tableView->addColumnItem(Base::ColumnItem(AIS_Time, QStringLiteral("ʵʱ�ź�ʱ��")));
			m_tableView->addColumnItem(Base::ColumnItem(AIS_Lon, QStringLiteral("����")));
			m_tableView->addColumnItem(Base::ColumnItem(AIS_Lat, QStringLiteral("γ��")));
			m_tableView->addColumnItem(Base::ColumnItem(AIS_Course, QStringLiteral("������")));
			m_tableView->addColumnItem(Base::ColumnItem(AIS_Truehead, QStringLiteral("������")));
			m_tableView->addColumnItem(Base::ColumnItem(AIS_Name, QStringLiteral("����")));
			m_tableView->addColumnItem(Base::ColumnItem(AIS_ShipType, QStringLiteral("�����Լ���������"), 200));
			m_tableView->addColumnItem(Base::ColumnItem(AIS_NavStatus, QStringLiteral("����״̬")));
			m_tableView->addColumnItem(Base::ColumnItem(AIS_Speed, QStringLiteral("�����ٶ�")));
			m_tableView->addColumnItem(Base::ColumnItem(AIS_Length, QStringLiteral("����(m)")));
			m_tableView->addColumnItem(Base::ColumnItem(AIS_Width, QStringLiteral("����(m)")));
			m_tableView->addColumnItem(Base::ColumnItem(AIS_BuildDate, QStringLiteral("����ʱ��")));
			m_tableView->addColumnItem(Base::ColumnItem(AIS_Port, QStringLiteral("������")));

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

	void AisDataPage::initConnect()
	{
	}

	void AisDataPage::createData()
	{
		QList<Datastruct::AisEntityData> listData;
		for (int i = 0; i < 15;  i++) {
			QDateTime current_date_time = QDateTime::currentDateTime();

			Datastruct::AisEntityData data;
			data.mmsi = 0;					/*!< ����MMSI */
			data.time = 1600;					/*!< ʵʱ�ź�ʱ�� */
			data.lon = 15;					/*!< ���� */
			data.lat = 16;					/*!< γ�� */
			data.course = 16;				/*!< ������ */
			data.truehead= 15+1;				/*!< ������ */
			data.name = QString("%1_%2").arg(QStringLiteral("�й�")).arg(i+1);				/*!< ���� */
			data.navStatus = 1;				/*!< ����״̬ */
			data.speed =16;				/*!< �����ٶ� */
			data.length = 160;				/*!< ���� */
			data.width = 43;				/*!< ���� */
			data.buildDate = current_date_time.toString(TIME_FORMAT);			/*!< ����ʱ�� */
			data.port = QStringLiteral("�й�");				/*!< ������ */

			listData.append(data);
		}

		m_tableModel->prepareData(listData);
	}

} //namespace Related