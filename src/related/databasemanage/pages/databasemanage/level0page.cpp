#include "level0page.h"

#include <QHBoxLayout>
#include <QDateTimeEdit>
#include <QLabel>
#include <QListView>
#include <QDebug>

namespace Related {

	Level0Page::Level0Page(QWidget *parent)
		: QWidget(parent)
	{
		init();
	}

	Level0Page::~Level0Page()
	{

	}

	void Level0Page::init()
	{
		m_tableView = new Base::RTableView();
		m_tableView->setFocusPolicy(Qt::NoFocus);
		m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
		m_tableView->setSelectionMode(QAbstractItemView::SingleSelection);

		m_tableView->addColumnItem(Base::ColumnItem(C_Id, QStringLiteral("����")));
		m_tableView->addColumnItem(Base::ColumnItem(C_Num, QStringLiteral("���")));
		m_tableView->addColumnItem(Base::ColumnItem(C_Timestamp, QStringLiteral("¼��ʱ��")));
		m_tableView->addColumnItem(Base::ColumnItem(C_ExperienceName, QStringLiteral("ʵ����")));
		m_tableView->addColumnItem(Base::ColumnItem(C_PlatformName, QStringLiteral("ƽ̨��")));
		m_tableView->addColumnItem(Base::ColumnItem(C_TimeLength, QStringLiteral("����ʱ��(s)")));
		m_tableView->addColumnItem(Base::ColumnItem(C_DataType, QStringLiteral("��������")));

		m_tableModel = new LevelModel0();
		m_tableModel->prepareData();

		m_tableView->setModel(m_tableModel);

		auto createButt = [](QString icon,QString text) {
			Base::RIconButton * butt = new Base::RIconButton();
			butt->setIconSize(Base::RIconButton::ICON_16);
			butt->setIcon(QIcon(icon));
			butt->setText(text);
			butt->setFont(QFont(QStringLiteral("΢���ź�"),10));
			butt->setMinimumSize(60, 30);

			return butt;
		};

		m_addButton = createButt(QStringLiteral(":/QYBlue/resource/qyblue/����.png"),QStringLiteral("����"));
		m_delButton = createButt(QStringLiteral(":/QYBlue/resource/qyblue/ɾ��.png"),QStringLiteral("ɾ��"));
		m_editButton = createButt(QStringLiteral(":/QYBlue/resource/qyblue/�༭.png"),QStringLiteral("�༭"));
		m_refreshButton = createButt(QStringLiteral(":/QYBlue/resource/qyblue/ˢ��.png"),QStringLiteral("ˢ��"));

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

		m_searchButton = createButt(QStringLiteral(":/QYBlue/resource/qyblue/����.png"), QStringLiteral("����"));
		m_advanceSearchButton = createButt(QStringLiteral(":/QYBlue/resource/qyblue/�߼�����.png"), QStringLiteral("�߼�����"));
		m_moreButton = createButt(QStringLiteral(":/QYBlue/resource/qyblue/����.png"), QStringLiteral("����"));

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
		QWidget * pageSwitch = new QWidget();
		pageSwitch->setObjectName("mainWidget");
		pageSwitch->setFixedHeight(35);
		QHBoxLayout * pageLayout = new QHBoxLayout();
		pageLayout->setContentsMargins(4, 4, 4, 4);
		
		m_firstButton = createButt(QStringLiteral(":/QYBlue/resource/qyblue/����ҳ.png"),QStringLiteral("��ҳ"));
		m_prePageButton = createButt(QStringLiteral(":/QYBlue/resource/qyblue/С�ں�.png"),QStringLiteral("��ҳ"));
		m_nextPageButton = createButt(QStringLiteral(":/QYBlue/resource/qyblue/���ں�.png"),QStringLiteral("��ҳ"));
		m_lastButton = createButt(QStringLiteral(":/QYBlue/resource/qyblue/��βҳ.png"),QStringLiteral("βҳ"));

		pageLayout->addStretch(1);

		m_pageItemCountBox = new QComboBox();
		m_pageItemCountBox->setFocusPolicy(Qt::NoFocus);
		m_pageItemCountBox->setView(new QListView());
		m_pageItemCountBox->addItem(QStringLiteral("30��/ҳ"));
		m_pageItemCountBox->addItem(QStringLiteral("50��/ҳ"));
		m_pageItemCountBox->addItem(QStringLiteral("100��/ҳ"));

		pageLayout->addWidget(m_pageItemCountBox);
		pageLayout->addSpacing(15);
		pageLayout->addWidget(m_firstButton);
		pageLayout->addWidget(m_prePageButton);
		pageLayout->addWidget(m_nextPageButton);
		pageLayout->addWidget(m_lastButton);
		pageLayout->addStretch(1);

		pageSwitch->setLayout(pageLayout);

		QVBoxLayout * vlayout = new QVBoxLayout();
		vlayout->setContentsMargins(4, 4, 4, 4);
		vlayout->addWidget(toolWidget);
		vlayout->addWidget(m_tableView);
		vlayout->addWidget(pageSwitch);

		setLayout(vlayout);
	}

} //namespace Related 