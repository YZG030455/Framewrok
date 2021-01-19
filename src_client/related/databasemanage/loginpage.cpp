#include "loginpage.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QResizeEvent>
#include <QDebug>

#include "customwidget/customwidgetcontainer.h"

namespace Related {

	LoginPage::LoginPage(QWidget *parent)
		: QWidget(parent)
	{
		init();
	}

	LoginPage::~LoginPage()
	{

	}

	void LoginPage::resizeEvent(QResizeEvent *event)
	{
		QSize windowSize = event->size();

		int x = (windowSize.width() - m_container->width()) / 2;
		int y = (windowSize.height() - m_container->height() ) / 2 - 20;
		m_container->move(x,y);

	}

	void LoginPage::respLogin()
	{
		emit switchToMainPage();
	}

	void LoginPage::init()
	{
		QWidget * mainWidget = new QWidget();
		mainWidget->setObjectName("Widget_LoginBackGround");

		QWidget * loginWidget = new QWidget();
		
		QLabel * titleLabel = new QLabel();
		titleLabel->setObjectName("Label_Login_TitleLabel");
		titleLabel->setAlignment(Qt::AlignCenter);
		titleLabel->setFixedHeight(40);
		titleLabel->setText(QStringLiteral("ĳˮ�����ݹ������"));

		m_userName = new QLineEdit();
		m_userName->setMinimumHeight(25);
		m_userName->setPlaceholderText(QStringLiteral("�������û���"));

		m_password = new QLineEdit();
		m_password->setEchoMode(QLineEdit::Password);
		m_password->setMinimumHeight(25);
		m_password->setPlaceholderText(QStringLiteral("����������"));

		m_loginButt = new Base::RIconButton();
		m_loginButt->setIconSize(Base::RIconButton::ICON_24);
		m_loginButt->setIcon(QIcon(QStringLiteral(":/QYBlue/resource/qyblue/��¼.png")));
		m_loginButt->setText(QStringLiteral("��¼"));
		connect(m_loginButt, SIGNAL(pressed()), this, SLOT(respLogin()));

		QVBoxLayout * vlayout = new QVBoxLayout();
		vlayout->addWidget(titleLabel);
		vlayout->addWidget(m_userName);
		vlayout->addWidget(m_password);
		vlayout->addWidget(m_loginButt);

		loginWidget->setLayout(vlayout);

		m_container = new CustomWidgetContainer(mainWidget);
		m_container->setFixedSize(400, 480);
		m_container->setContent(loginWidget);
		m_container->show();

		QHBoxLayout * layout = new QHBoxLayout();
		layout->setContentsMargins(0, 0, 0, 0);
		layout->addWidget(mainWidget);
		setLayout(layout);
	}

} //namespace Related 