#include "datasamplepage.h"

#include <QHBoxLayout>
#include <QDateTimeEdit>
#include <QLabel>
#include <QListView>
#include <QDebug>

#include "../customwidget/pageswitchbar.h"

namespace Related {

	datasamplepage::datasamplepage(QWidget *parent)
		: QWidget(parent)
	{
		init();
		crerateAction();
	}

	datasamplepage::~datasamplepage()
	{
	}

	void datasamplepage::contextMenuEvent(QContextMenuEvent * event)
	{
		m_pop_menu->clear();
		m_pop_menu->addAction(m_hcAction);
		m_pop_menu->addAction(m_csbAction);
		m_pop_menu->addAction(m_swtzAction);
		m_pop_menu->addAction(m_mbxxAction);
		m_pop_menu->addAction(m_sbxxAction);
		m_pop_menu->addAction(m_scAction);
		m_pop_menu->exec(QCursor::pos());
		event->accept();
	}

	void datasamplepage::slotLeadingInButton()
	{
		emit signalDataGather();
	}

	void datasamplepage::slotInspectAction()
	{
		emit signalInspectData();
	}

	void datasamplepage::init()
	{
		auto createButt = [](QString icon, QString text) {
			Base::RIconButton * butt = new Base::RIconButton();
			butt->setIconSize(Base::RIconButton::ICON_16);
			butt->setIcon(QIcon(icon));
			butt->setText(text);
			butt->setFont(QFont(QStringLiteral("΢���ź�"), 10));
			butt->setMinimumSize(60, 30);
			return butt;
		};

		m_leadingInButton = createButt(QStringLiteral(":/QYBlue/resource/qyblue/����.png"), QStringLiteral("����"));
		m_gatherButton = createButt(QStringLiteral(":/QYBlue/resource/qyblue/����.png"), QStringLiteral("�ɼ�"));

		connect(m_gatherButton, SIGNAL(clicked()), this, SLOT(slotLeadingInButton()));

		m_identificationQueueButton = createButt(QStringLiteral(":/QYBlue/resource/qyblue/����.png"), QStringLiteral("ʶ�����"));
		m_retrievalButton = createButt(QStringLiteral(":/QYBlue/resource/qyblue/ˢ��.png"), QStringLiteral("����"));
		m_congnizanceButton = createButt(QStringLiteral(":/QYBlue/resource/qyblue/����.png"), QStringLiteral("ͬһ���϶�"));
		m_batchDeleButton = createButt(QStringLiteral(":/QYBlue/resource/qyblue/ɾ��.png"), QStringLiteral("����ɾ��"));
		QWidget *totalWidget = new QWidget();
		QHBoxLayout *t_totalLayout = new QHBoxLayout();
		t_totalLayout->addWidget(m_leadingInButton);
		t_totalLayout->addWidget(m_gatherButton);
		t_totalLayout->addWidget(m_identificationQueueButton);
		t_totalLayout->addWidget(m_retrievalButton);
		t_totalLayout->addWidget(m_congnizanceButton);
		t_totalLayout->addWidget(m_batchDeleButton);
		t_totalLayout->addStretch();
		t_totalLayout->setContentsMargins(0,0,0,0);
		t_totalLayout->setSpacing(1);
		totalWidget->setLayout(t_totalLayout);
		
		//
		m_tableView = new Base::RTableView();
		m_tableView->setFocusPolicy(Qt::NoFocus);

		m_tableModel = new datasamplemodel();
		m_tableModel->prepareData();
		m_tableView->setModel(m_tableModel);

		m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
		m_tableView->setSelectionMode(QAbstractItemView::SingleSelection);
		m_tableView->addColumnItem(Base::ColumnItem(D_Id, QStringLiteral("���"),70));
		m_tableView->addColumnItem(Base::ColumnItem(D_Time, QStringLiteral("ʱ��"),150));
		m_tableView->addColumnItem(Base::ColumnItem(D_BatchNumber, QStringLiteral("����")));
		m_tableView->addColumnItem(Base::ColumnItem(D_LocalDistinguish, QStringLiteral("����ʶ��")));
		m_tableView->addColumnItem(Base::ColumnItem(D_Result, QStringLiteral("ͬһ�϶����")));

		m_tableView->setContentsMargins(0, 0, 0, 0);

		PageSwitchBar * pageSwitch = new PageSwitchBar();
		connect(pageSwitch, SIGNAL(perPageNumsChanged(int)), m_tableModel, SLOT(setFixedPageRowCount(int)));

		QVBoxLayout * mainVLayout = new QVBoxLayout();
		mainVLayout->addWidget(totalWidget);
		mainVLayout->addWidget(m_tableView);
		mainVLayout->addWidget(pageSwitch);
		mainVLayout->setContentsMargins(0,0,0,0);
		mainVLayout->setSpacing(1);
		setLayout(mainVLayout);
	}

	void datasamplepage::crerateAction()
	{
		m_pop_menu = new QMenu();
		m_hcAction = new QAction(this);
		m_hcAction->setText(QStringLiteral("�˲�"));
		connect(m_hcAction, SIGNAL(triggered()), this,SLOT(slotInspectAction()));

		m_csbAction = new QAction(this);
		m_csbAction->setText(QStringLiteral("��ʶ��"));
		m_swtzAction = new QAction(this);
		m_swtzAction->setText(QStringLiteral("���������༭"));
		m_mbxxAction = new QAction(this);
		m_mbxxAction->setText(QStringLiteral("Ŀ����Ϣ�޸�"));
		m_sbxxAction = new QAction(this);
		m_sbxxAction->setText(QStringLiteral("ʶ����Ϣ�ϱ�"));
		m_scAction = new QAction(this);
		m_scAction->setText(QStringLiteral("ɾ��"));
	}

}//namespace Related 