#include "level1page.h"

#include <QHBoxLayout>
#include <QDateTimeEdit>
#include <QLabel>
#include <QListView>
#include <QDebug>

#include "../util.h"
#include "../customwidget/pageswitchbar.h"

namespace Related {

	Level1Page::Level1Page(QWidget *parent)
		: QWidget(parent)
	{
		init();
	}

	Level1Page::~Level1Page()
	{

	}

	void Level1Page::setPageNum(int newPage)
	{
		m_tableModel->setPageNum(newPage);
		m_tableModel->refresh();
	}

	void Level1Page::init()
	{
		m_tableView = new Base::RTableView();
		m_tableView->setFocusPolicy(Qt::NoFocus);
		m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
		m_tableView->setSelectionMode(QAbstractItemView::SingleSelection);

		m_tableView->addColumnItem(Base::ColumnItem(L1_Id, QStringLiteral("����")));
		m_tableView->addColumnItem(Base::ColumnItem(L1_Num, QStringLiteral("���")));
		m_tableView->addColumnItem(Base::ColumnItem(L1_Timestamp, QStringLiteral("ƽ̨��")));
		m_tableView->addColumnItem(Base::ColumnItem(L1_PlatformName, QStringLiteral("ƽ̨��Ϣ")));
		m_tableView->addColumnItem(Base::ColumnItem(L1_TimeLength, QStringLiteral("����ʱ��")));
		m_tableView->addColumnItem(Base::ColumnItem(L1_DataType, QStringLiteral("��������")));

		m_tableModel = new LevelModel0();
		m_tableModel->prepareData();

		m_tableView->setModel(m_tableModel);

		m_addButton = Util::createButt(QStringLiteral(":/QYBlue/resource/qyblue/����.png"),QStringLiteral("����"));
		m_delButton = Util::createButt(QStringLiteral(":/QYBlue/resource/qyblue/ɾ��.png"),QStringLiteral("ɾ��"));
		m_editButton = Util::createButt(QStringLiteral(":/QYBlue/resource/qyblue/�༭.png"),QStringLiteral("�༭"));
		m_refreshButton = Util::createButt(QStringLiteral(":/QYBlue/resource/qyblue/ˢ��.png"),QStringLiteral("ˢ��"));

		//ʱ��ɸѡ
		QWidget * timeRangeSelect = new QWidget();
		QHBoxLayout * timeLayout = new QHBoxLayout();

		QLabel * inputTime = new QLabel();
		inputTime->setText(QStringLiteral("¼��ʱ��:"));

		QLabel * toTime = new QLabel();
		toTime->setText(QStringLiteral(" �� "));

		QDateTimeEdit * startTimeEdit = new QDateTimeEdit();
		startTimeEdit->setMinimumHeight(25);

		QDateTimeEdit * endTimeEdit = new QDateTimeEdit();
		endTimeEdit->setMinimumHeight(25);

		timeLayout->addWidget(inputTime);
		timeLayout->addWidget(startTimeEdit);
		timeLayout->addWidget(toTime);
		timeLayout->addWidget(endTimeEdit);

		timeRangeSelect->setLayout(timeLayout);

		m_searchButton = Util::createButt(QStringLiteral(":/QYBlue/resource/qyblue/����.png"), QStringLiteral("����"));
		m_advanceSearchButton = Util::createButt(QStringLiteral(":/QYBlue/resource/qyblue/�߼�����.png"), QStringLiteral("�߼�����"));
		m_moreButton = Util::createButt(QStringLiteral(":/QYBlue/resource/qyblue/����.png"), QStringLiteral("����"));

		QWidget * toolWidget = new QWidget();
		QHBoxLayout * toolLayout = new QHBoxLayout();
		toolLayout->setContentsMargins(0, 0, 0, 0);

		toolLayout->addWidget(m_addButton);
		toolLayout->addWidget(m_delButton);
		toolLayout->addWidget(m_editButton);
		toolLayout->addWidget(m_refreshButton);
		toolLayout->addStretch(1);

		toolLayout->addWidget(timeRangeSelect);
		toolLayout->addWidget(m_searchButton);
		toolLayout->addWidget(m_advanceSearchButton);
		toolLayout->addWidget(m_moreButton);

		toolWidget->setLayout(toolLayout);

		//ҳ���л�
		PageSwitchBar * pageSwitch = new PageSwitchBar();
		pageSwitch->setDataSize(m_tableModel->datasSize());
		connect(pageSwitch, SIGNAL(perPageNumsChanged(int)), m_tableModel, SLOT(setFixedPageRowCount(int)));
		connect(pageSwitch, SIGNAL(switchPage(int)), this, SLOT(setPageNum(int)));

		QVBoxLayout * vlayout = new QVBoxLayout();
		vlayout->setContentsMargins(4, 4, 4, 4);
		vlayout->addWidget(toolWidget);
		vlayout->addWidget(m_tableView);
		vlayout->addWidget(pageSwitch);

		setLayout(vlayout);
	}

} //namespace Related 