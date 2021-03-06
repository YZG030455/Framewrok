#include "level0page.h"

#include <QHBoxLayout>
#include <QDateTimeEdit>
#include <QLabel>
#include <QListView>
#include <QDebug>

#include "../../utils/util.h"
#include "../../global.h"
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

		m_tableView->addColumnItem(Base::ColumnItem(L0_Id, QStringLiteral("索引")));
		m_tableView->addColumnItem(Base::ColumnItem(L0_Num, QStringLiteral("编号")));
		m_tableView->addColumnItem(Base::ColumnItem(L0_Name, QStringLiteral("文件名")));
		m_tableView->addColumnItem(Base::ColumnItem(L0_Timestamp, QStringLiteral("录入时间"), 150));
		m_tableView->addColumnItem(Base::ColumnItem(L0_ExperienceName, QStringLiteral("实验名")));
		m_tableView->addColumnItem(Base::ColumnItem(L0_PlatformName, QStringLiteral("平台信息")));
		m_tableView->addColumnItem(Base::ColumnItem(L0_SampleRate, QStringLiteral("采样率")));
		m_tableView->addColumnItem(Base::ColumnItem(L0_TimeLength, QStringLiteral("数据时长(s)")));
		m_tableView->addColumnItem(Base::ColumnItem(L0_DataType, QStringLiteral("数据类型")));
		m_tableView->addColumnItem(Base::ColumnItem(L0_DataSource, QStringLiteral("数据来源")));

		m_addButton = Util::createButt(WRAP_RESOURCE(新增),QStringLiteral("新增"));
		m_delButton = Util::createButt(WRAP_RESOURCE(删除),QStringLiteral("删除"));
		m_editButton = Util::createButt(WRAP_RESOURCE(编辑),QStringLiteral("编辑"));
		m_refreshButton = Util::createButt(WRAP_RESOURCE(刷新),QStringLiteral("刷新"));

		//时间筛选
		QWidget * timeRangeSelect = new QWidget();
		QHBoxLayout * timeLayout = new QHBoxLayout();

		QLabel * inputTime = new QLabel();
		inputTime->setText(QStringLiteral("录入时间:"));

		QLabel * toTime = new QLabel();
		toTime->setText(QStringLiteral(" 至 "));

		QDateTimeEdit * startTimeEdit = new QDateTimeEdit();
		startTimeEdit->setMinimumHeight(25);

		QDateTimeEdit * endTimeEdit = new QDateTimeEdit();
		endTimeEdit->setMinimumHeight(25);

		timeLayout->addWidget(inputTime);
		timeLayout->addWidget(startTimeEdit);
		timeLayout->addWidget(toTime);
		timeLayout->addWidget(endTimeEdit);

		timeRangeSelect->setLayout(timeLayout);

		m_searchButton = Util::createButt(WRAP_RESOURCE(搜索), QStringLiteral("搜索"));
		m_advanceSearchButton = Util::createButt(WRAP_RESOURCE(高级搜索), QStringLiteral("高级搜索"));
		m_moreButton = Util::createButt(WRAP_RESOURCE(更多), QStringLiteral("更多"));

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

		//页面切换
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