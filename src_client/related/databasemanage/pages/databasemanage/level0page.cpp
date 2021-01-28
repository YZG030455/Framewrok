#include "level0page.h"

#include <QHBoxLayout>
#include <QDateTimeEdit>
#include <QLabel>
#include <QListView>
#include <QDebug>

#include "../../utils/util.h"
#include "../../customwidget/pageswitchbar.h"
#include "../../customwidget/customwidgetcontainer.h"

namespace Related {

	Level0Page::Level0Page(QWidget *parent)
		: QWidget(parent)
	{
		init();
	}

	Level0Page::~Level0Page()
	{

	}

	void Level0Page::setPageNum(int newPage)
	{
		m_tableModel->setPageNum(newPage);
		m_tableModel->refresh();
	}

	void Level0Page::init()
	{
		m_tableView = new Base::RTableView();
		m_tableView->setFocusPolicy(Qt::NoFocus);
		m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
		m_tableView->setSelectionMode(QAbstractItemView::SingleSelection);

		m_tableModel = new LevelModel0();
		m_tableModel->prepareData();

		m_tableView->setModel(m_tableModel);

		m_tableView->addColumnItem(Base::ColumnItem(L0_Id, QStringLiteral("����")));
		m_tableView->addColumnItem(Base::ColumnItem(L0_Num, QStringLiteral("���")));
		m_tableView->addColumnItem(Base::ColumnItem(L0_Name, QStringLiteral("�ļ���")));
		m_tableView->addColumnItem(Base::ColumnItem(L0_Timestamp, QStringLiteral("¼��ʱ��"), 150));
		m_tableView->addColumnItem(Base::ColumnItem(L0_ExperienceName, QStringLiteral("ʵ����")));
		m_tableView->addColumnItem(Base::ColumnItem(L0_PlatformName, QStringLiteral("ƽ̨��Ϣ")));
		m_tableView->addColumnItem(Base::ColumnItem(L0_SampleRate, QStringLiteral("������")));
		m_tableView->addColumnItem(Base::ColumnItem(L0_TimeLength, QStringLiteral("����ʱ��(s)")));
		m_tableView->addColumnItem(Base::ColumnItem(L0_DataType, QStringLiteral("��������")));
		m_tableView->addColumnItem(Base::ColumnItem(L0_DataSource, QStringLiteral("������Դ")));

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

		CustomWidgetContainer * cwidget = new CustomWidgetContainer();
		cwidget->setContent(toolWidget);

		QWidget * twidget = new QWidget();
		QVBoxLayout * cvlayout = new QVBoxLayout();
		cvlayout->setContentsMargins(0, 0, 0, 0);
		cvlayout->addWidget(m_tableView);
		cvlayout->addWidget(pageSwitch);
		twidget->setLayout(cvlayout);

		CustomWidgetContainer * ctableView = new CustomWidgetContainer();
		ctableView->setContent(twidget);

		QVBoxLayout * vlayout = new QVBoxLayout();
		vlayout->setContentsMargins(4, 4, 4, 4);
		vlayout->addWidget(cwidget);
		vlayout->addWidget(ctableView);

		setLayout(vlayout);
	}

} //namespace Related 