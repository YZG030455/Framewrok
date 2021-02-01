#include "datapreviewpage.h"

#include <QDebug>
#include <QListView>

#include "../../utils/util.h"
#include "../../customwidget/customwidgetcontainer.h"
#include "subpage/wavorigindatawindow.h"

namespace Related {

	DataPreviewPage::DataPreviewPage(QWidget *parent)
		: AbstractPage(parent),
		m_firstLoadData(false)
	{
		init();
		initConnect();
	}

	DataPreviewPage::~DataPreviewPage()
	{

	}

	PageType DataPreviewPage::getPageType() const
	{
		return Page_TaskAnalyse_DataOverview;
	}

	void DataPreviewPage::prepareBringToTop()
	{
		if (m_firstLoadData) {

			m_firstLoadData = false;
		}
	}

	void DataPreviewPage::setTaskId(QString taskId)
	{
	}

	void DataPreviewPage::respToolButtPressed(OperationToolsPage::ButtType type)
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

	void DataPreviewPage::slotTableDoubleClicked(QModelIndex index)
	{
		QString dataId;

		emit signalOpenAudioDataPage(dataId);
	}

	void DataPreviewPage::setPageNum(int page)
	{
	}

	void DataPreviewPage::setFixedPageRowCount(int pageItemCount)
	{
		m_tableModel->setFixedPageRowCount(pageItemCount);
	}

	void DataPreviewPage::showTableContextMenu(const QPoint & point)
	{
		m_tableMenu->exec(QCursor::pos());
	}

	void DataPreviewPage::analyseWav(bool flag)
	{
		slotTableDoubleClicked(QModelIndex());
	}

	void DataPreviewPage::viewWavOriginalData(bool flag)
	{
		WavOriginDataWindow window(this);
		window.exec();
	}

	void DataPreviewPage::init()
	{
		CustomWidgetContainer * cwidget = new CustomWidgetContainer();
		{
			m_operationToolsPage = new OperationToolsPage();
			connect(m_operationToolsPage, SIGNAL(buttPressed(OperationToolsPage::ButtType)), this, SLOT(respToolButtPressed(OperationToolsPage::ButtType)));

			QLabel * label = new QLabel();
			label->setText(QStringLiteral("���ƽ̨:"));

			QComboBox * comboBox = new QComboBox();
			comboBox->setView(new QListView());
			comboBox->setMinimumSize(120, 30);

			QStringList list;
			list << QStringLiteral("����ƽ̨") << QStringLiteral("HXJ01") << QStringLiteral("HXJ02") << QStringLiteral("HXJ03");
			comboBox->addItems(list);

			QWidget * widget = new QWidget();
			QHBoxLayout * hLayout = new QHBoxLayout();
			hLayout->addWidget(m_operationToolsPage);
			hLayout->addStretch();
			hLayout->addWidget(label);
			hLayout->addWidget(comboBox);
			hLayout->setContentsMargins(0, 0, 0, 0);
			widget->setLayout(hLayout);
			cwidget->setContent(widget);
		}

		CustomWidgetContainer * ctableView = new CustomWidgetContainer();
		{
			m_tableModel = new DataOverviewMolel();

			m_tableView = new Base::RTableView();
			m_tableView->setContextMenuPolicy(Qt::CustomContextMenu);
			m_tableView->setModel(m_tableModel);
			m_tableView->setFocusPolicy(Qt::NoFocus);
			m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
			m_tableView->setSelectionMode(QAbstractItemView::SingleSelection);

			m_tableView->addColumnItem(Base::ColumnItem(T_Index, QStringLiteral("����"),60));
			m_tableView->addColumnItem(Base::ColumnItem(T_TargetName, QStringLiteral("���"), 140));
			m_tableView->addColumnItem(Base::ColumnItem(T_Edttime, QStringLiteral("¼��ʱ��"), 180));
			m_tableView->addColumnItem(Base::ColumnItem(T_Tonnage, QStringLiteral("������"), 180));
			m_tableView->addColumnItem(Base::ColumnItem(T_AxlesNumber, QStringLiteral("ƽ̨��")));
			m_tableView->addColumnItem(Base::ColumnItem(T_Datalength, QStringLiteral("����ʱ��")));
			m_tableView->addColumnItem(Base::ColumnItem(T_Type, QStringLiteral("����")));

			connect(m_tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slotTableDoubleClicked(QModelIndex)));
			connect(m_tableView, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showTableContextMenu(const QPoint &)));

			m_tableModel->prepareData();

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

		{
			m_tableMenu = new QMenu();

			m_analyseWav = new QAction();
			m_analyseWav->setText(QStringLiteral("������Ƶ"));
			connect(m_analyseWav, SIGNAL(triggered(bool)),this,SLOT(analyseWav(bool)));

			m_viewOriginalData = new QAction();
			m_viewOriginalData->setText(QStringLiteral("�鿴ԭʼ����"));
			connect(m_viewOriginalData, SIGNAL(triggered(bool)),this,SLOT(viewWavOriginalData(bool)));

			m_tableMenu->addAction(m_analyseWav);
			m_tableMenu->addAction(m_viewOriginalData);
		}


		QVBoxLayout * vlayout = new QVBoxLayout();
		vlayout->setContentsMargins(4, 4, 4, 4);
		vlayout->addWidget(cwidget);
		vlayout->addWidget(ctableView);
		setLayout(vlayout);
	}

	void DataPreviewPage::initConnect()
	{
	}

}//namespace Related 