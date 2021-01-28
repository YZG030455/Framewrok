#include "leftpanel.h"

#include <qboxlayout.h>
#include <QDebug>

#include "../customwidget\rlistwidget.h"
#include "../datastruct.h"

namespace Related {

	LeftPanel::LeftPanel(QWidget *parent)
		: QWidget(parent), m_expandStateWidth(276), m_contractionWidth(100)
	{
		init();
		respLeftPanelExpand(true);
		setFixedWidth(m_expandStateWidth);

		switchViewModel(SystemView);
	}

	LeftPanel::~LeftPanel()
	{
	}

	void LeftPanel::switchViewModel(ViewModel model)
	{
		m_currViewModel = model;
		m_backToSystemViewButt->setVisible(model == TaskView);

		if (model == SystemView) {
			m_systemListWidget->setCurrentIndex(0);
		}
		else if (model == TaskView) {
			m_taskListWidget->setCurrentIndex(0);
		}
		m_leftMenuContainer->setCurrentIndex(static_cast<int>(model));
	}

	int LeftPanel::getCurrentPage() const
	{
		if (m_currViewModel == SystemView) {
			return m_systemListWidget->currentIndex();
		}
		else if (m_currViewModel == TaskView) {
			return m_taskListWidget->currentIndex();
		}
	}

	void LeftPanel::respLeftPanelExpand(bool checked)
	{
		m_systemListWidget->setExpanded(checked);
		m_taskListWidget->setExpanded(checked);

		m_notifyButt->setTextVisible(checked);
		m_backToSystemViewButt->setTextVisible(checked);

		if (checked) {
			m_prgoramIcon->setText(QStringLiteral("���ݹ���ϵͳ���"));
			m_expandButt->setIcon(QIcon(QStringLiteral(":/QYBlue/resource/qyblue/��������.png")));
			m_expandButt->setToolTip(QStringLiteral("�۵�"));
		}
		else {
			m_prgoramIcon->setText(QStringLiteral("QT"));
			m_expandButt->setIcon(QIcon(QStringLiteral(":/QYBlue/resource/qyblue/����չ��.png")));
			m_expandButt->setToolTip(QStringLiteral("չ��"));
		}
	}

	/*!
	 * @brief ����ϵͳ��ͼ
	 */
	void LeftPanel::backToSystemView()
	{
		switchViewModel(SystemView);
		emit switchToSystemView();
	}

	void LeftPanel::init()
	{
		QWidget * mainWidget = new QWidget();
		mainWidget->setObjectName("Widget_LeftPanel");

		m_prgoramIcon = new QLabel(mainWidget);
		m_prgoramIcon->setObjectName("Label_ProgramName");

		m_expandButt = new Base::RIconButton(mainWidget);
		m_expandButt->setCheckable(true);
		m_expandButt->setChecked(true);
		m_expandButt->setIconSize(Base::RIconButton::ICON_24);
		m_expandButt->setContentsMargins(0,0,0,0);
		m_expandButt->setFixedSize(32, 32);

		m_expandButt->disableColor(Base::RIconButton::Color_NormalBorder);
		m_expandButt->disableColor(Base::RIconButton::Color_HoverBorder);
		m_expandButt->disableColor(Base::RIconButton::Color_CheckedBorder);
		m_expandButt->disableColor(Base::RIconButton::Color_CheckedBackGround);

		connect(m_expandButt, &Base::RIconButton::clicked, [&](bool clicked) {
			if (clicked) {
				m_animation.addVariantAnimation(m_contractionWidth, m_expandStateWidth,[&](QVariant val) {
				this->setFixedWidth(val.toInt());
				});
			}
			else {
				m_animation.addVariantAnimation(m_expandStateWidth, m_contractionWidth, [&](QVariant val) {
					this->setFixedWidth(val.toInt());
				});
			}
			respLeftPanelExpand(clicked);
		});

		QHBoxLayout * tmpLayout = new QHBoxLayout();
		tmpLayout->addWidget(m_prgoramIcon);
		tmpLayout->addWidget(m_expandButt);
		
		QWidget * tmpWidget = new QWidget();
		tmpWidget->setLayout(tmpLayout);
		tmpWidget->setFixedHeight(80);

		//ϵͳ���˵�
		m_systemListWidget = new RListWidget(this);
		connect(m_systemListWidget, SIGNAL(currentIndexChanged(int)),this,SIGNAL(currentIndexChanged(int)));

		m_systemListWidget->addItem(Page_SystemMainPage,QStringLiteral("����ͳ��"), QIcon(QStringLiteral(":/QYBlue/resource/qyblue/��ҳicon.png")));
		m_systemListWidget->addItem(Page_TargetDatabase,QStringLiteral("Ŀ���"), QIcon(QStringLiteral(":/QYBlue/resource/qyblue/���ݹ���icon.png")));
		m_systemListWidget->addItem(Page_Setting,QStringLiteral("ϵͳ����"), QIcon(QStringLiteral(":/QYBlue/resource/qyblue/ϵͳ����icon.png")));
		m_systemListWidget->setCurrentIndex(0);

		//���񼶲˵�
		m_taskListWidget = new RListWidget(this);
		connect(m_taskListWidget, SIGNAL(currentIndexChanged(int)),this,SIGNAL(currentIndexChanged(int)));
		m_taskListWidget->addItem(Page_TaskOverviewPage, QStringLiteral("�������"), QIcon(QStringLiteral(":/QYBlue/resource/qyblue/����.png")));
		m_taskListWidget->addItem(Page_TaskRecordPage, QStringLiteral("�����¼"), QIcon(QStringLiteral(":/QYBlue/resource/qyblue/��¼.png")));
		m_taskListWidget->addItem(Page_TaskDataAnalyse, QStringLiteral("�������"), QIcon(QStringLiteral(":/QYBlue/resource/qyblue/���ݷ���icon.png")));
		m_taskListWidget->setCurrentIndex(0);

		m_leftMenuContainer = new QStackedWidget();
		m_leftMenuContainer->addWidget(m_systemListWidget);
		m_leftMenuContainer->addWidget(m_taskListWidget);

		QSize iconSize(40, 40);
		QFont iconFont(QStringLiteral("΢���ź�"),11);
		Base::RIconButton::ColorChooses disableColors = Base::RIconButton::Color_NormalBorder | Base::RIconButton::Color_CheckedBorder
			| Base::RIconButton::Color_CheckedBorder | Base::RIconButton::Color_HoverBackground | Base::RIconButton::Color_HoverBorder;

		auto setButtonProop = [&](Base::RIconButton * butt,QString text,QString pixmap) {
			butt->setIconTextSpacing(15);
			butt->setTextFont(iconFont);
			butt->setIconSize(Base::RIconButton::ICON_24);
			butt->disableColors(disableColors);
			butt->enableColor(Base::RIconButton::Color_NormalText, QColor(255, 255, 255, 120));
			butt->enableColor(Base::RIconButton::Color_HoverText, QColor(255, 255, 255));
			butt->setText(text);
			butt->setIcon(QIcon(pixmap));
		};

		m_notifyButt = new Base::RIconButton();
		setButtonProop(m_notifyButt, QStringLiteral("֪ͨ"), QStringLiteral(":/QYBlue/resource/qyblue/֪ͨ.png"));	
		
		m_backToSystemViewButt = new Base::RIconButton();
		m_backToSystemViewButt->setToolTip(QStringLiteral("�����������ҳ��"));
		connect(m_backToSystemViewButt, SIGNAL(clicked()), this, SLOT(backToSystemView()));
		setButtonProop(m_backToSystemViewButt, QStringLiteral("����"), QStringLiteral(":/QYBlue/resource/qyblue/����.png"));

		QWidget * bottomWidget = new QWidget();
		QVBoxLayout * bottomLayout = new QVBoxLayout();
		bottomLayout->setSpacing(15);
		bottomLayout->setContentsMargins(9, 9, 9, 15);
		bottomLayout->addWidget(m_backToSystemViewButt);
		bottomLayout->addWidget(m_notifyButt);
		bottomWidget->setLayout(bottomLayout);
		bottomWidget->setFixedHeight(iconSize.height() * bottomLayout->count() + (bottomLayout->count() - 1) * bottomLayout->spacing());

		QHBoxLayout * bottomHorizonalLayout = new QHBoxLayout();
		bottomHorizonalLayout->addStretch(1);
		bottomHorizonalLayout->addWidget(bottomWidget);
		bottomHorizonalLayout->addStretch(1);

		QVBoxLayout * mainLayout = new QVBoxLayout();
		mainLayout->setContentsMargins(0, 0, 0, 0);
		mainLayout->addWidget(tmpWidget);
		mainLayout->addWidget(m_leftMenuContainer);
		mainLayout->addLayout(bottomHorizonalLayout);
		mainWidget->setLayout(mainLayout);

		QVBoxLayout * layout = new QVBoxLayout();
		layout->setContentsMargins(0, 0, 0, 0);
		layout->addWidget(mainWidget);
		setLayout(layout);
	}

} //namespace Related 