#include "loginpage.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QResizeEvent>
#include <QDebug>

#include <base\util\rutil.h>
#include <base\selfwidget\rmessagebox.h>

#include "../customwidget/customwidgetcontainer.h"
#include "../net/datanetconnector.h"
#include "../net/filenetconnector.h"
#include "../net/connectormanage.h"
#include "../net/signaldispatch.h"
#include "../utils/util.h"
#include "../global.h"

namespace Related {

	LoginPage::LoginPage(QWidget *parent)
		: QWidget(parent), m_loginModel(true), m_isLoginState(true)
	{
		init();
		initConnect();
		loadNetConfig();
		updateReconnConfig();

		qRegisterMetaType<Datastruct::ConnectionType>("Datastruct::ConnectionType");
	}

	LoginPage::~LoginPage()
	{

	}

	void LoginPage::resizeEvent(QResizeEvent *event)
	{
		QSize windowSize = event->size();

		int x = windowSize.width() - m_container->width() * 1.5;
		int y = (windowSize.height() - m_container->height()) / 2;
		m_container->move(x, y);
	}

	bool LoginPage::eventFilter(QObject *watched, QEvent *event)
	{
		if (watched == m_loginWidget) {
			if (event->type() == QEvent::Resize) {
				m_userRegistSetting->move(QPoint(m_loginWidget->width() / 2 - 5 - m_userRegistSetting->width(), m_loginWidget->height() - m_userRegistSetting->height() - 10));
				m_systemSetting->move(QPoint(m_loginWidget->width() / 2 + 5, m_loginWidget->height() - m_systemSetting->height() - 10));
			}
		}
		return QWidget::eventFilter(watched, event);
	}

	/*!
	 * @brief ����������Զ�����ݡ��ļ�������
	 */
	void LoginPage::connectToServer()
	{
		START_WAIT;
		ConnectorManage::instance()->startConnect(m_ipWidget->getIPString(), m_dataPortWidget->text().toInt(), m_filePortWidget->text().toInt());
	}

	/*!
	 * @brief ��Ӧ�û����������������
	 * @detials �����û���ε��
	 */
	void LoginPage::reConnectServer()
	{
		if (!ConnectorManage::instance()->allNetConnected()) {
			connectToServer();
		}
	}

	void LoginPage::respConnectResult(Datastruct::ConnectionType type, bool connected, QString errorInfo)
	{
		if (connected) {
			respNetConnected(type, connected);
		}
		else {
			END_WAIT;
			Util::showWarning(this, errorInfo);
		}
	}

	/*!
	 * @brief ���������Ƿ����ӳɹ��ź�
	 * @param type ������·����
	 * @param connected true:�������ӳɹ���false:��������ʧ��
	 */
	void LoginPage::respNetConnected(Datastruct::ConnectionType type, bool connected)
	{
		if (connected) {
			if (type == Datastruct::Data_Connection) {
				if (m_isLoginState) {
					if (m_loginModel) {
						Datastruct::UserLoginRequest request;
						request.m_name = m_userName->text();
						request.m_password = Base::RUtil::MD5(m_password->text());

						DataNetConnector::instance()->write(request);
					}
					else {
						Datastruct::UserRegistRequest request;
						request.m_name = m_registUserName->text();
						request.m_password = Base::RUtil::MD5(m_registPassword1->text());

						DataNetConnector::instance()->write(request);
					}
				}

				Global::G_Notify->information(QStringLiteral("���ݴ�����·����������!"));
			}
			else if (type == Datastruct::File_Connection) {
				Global::G_Notify->information(QStringLiteral("�ļ�������·����������!"));
			}

			END_WAIT;
			emit netStateChanged(type, true);
		}
		else {

			END_WAIT;
			emit netStateChanged(type, false);

			if (type == Datastruct::Data_Connection) {
				Util::showWarning(this, QStringLiteral("�������ݷ�����ʧ�ܣ�������������."));
			}
			else if (type == Datastruct::File_Connection) {
				Util::showWarning(this, QStringLiteral("�����ļ�������ʧ�ܣ�������������."));
			}
		}
	}

	/*! 
	 * @brief ��Ӧ������������֪ͨ
	 * @param type ������������
	 * @param times ������������
	 */
	void LoginPage::respReconnResult(Datastruct::ConnectionType type, int times)
	{
		if (type == Datastruct::Data_Connection) {
			Global::G_Notify->information(QString(QStringLiteral("��%1���������ݷ�����!")).arg(times));
		}
		else if (type == Datastruct::File_Connection) {
			Global::G_Notify->information(QString(QStringLiteral("��%1�������ļ�������!")).arg(times));
		}
	}

	/*!
	 * @brief �����û���¼�����Ӧ
	 * @param response �û���¼�������
	 */
	void LoginPage::processUserLoginResponse(const Datastruct::UserLoginResponse & response)
	{
		if (response.m_loginResult) {
			m_isLoginState = false;
			emit switchToMainPage();
			Global::G_UserEntity = response.m_userInfo;
		}
		else {
			Util::showWarning(this, Datastruct::G_StrError(response.m_errorCode));
		}
	}

	void LoginPage::processUserRegistResponse(const Datastruct::UserRegistResponse & response)
	{
		if (response.m_loginResult) {
			Util::showInformation(this, QStringLiteral("ע��ɹ�!"));
			respCancelRegist();
		}
		else {
			Util::showWarning(this, Datastruct::G_StrError(response.m_errorCode));
		}
	}

	void LoginPage::showSystemSetting()
	{
		m_systemWidget->setGeometry(QRect(QPoint(0, m_loginWidget->height()), m_loginWidget->size()));
		m_animation.addAnimation(m_systemWidget, QRect(QPoint(0, 0), m_loginWidget->size()), [&]() {
			loadNetConfig();
		});
		m_systemWidget->show();
	}

	void LoginPage::respSave()
	{
		ConfigKey ckey;
		Base::RUtil::setGlobalValue(ckey.m_netGroupId, ckey.m_remoteServerIp, m_ipWidget->getIPString());
		Base::RUtil::setGlobalValue(ckey.m_netGroupId, ckey.m_remoteServerDataPort, m_dataPortWidget->text());
		Base::RUtil::setGlobalValue(ckey.m_netGroupId, ckey.m_remoteServerFilePort, m_filePortWidget->text());
		Base::RUtil::setGlobalValue(ckey.m_netGroupId, ckey.m_netAutoReconnect, m_autoReconnet->isChecked());
		Base::RUtil::setGlobalValue(ckey.m_netGroupId, ckey.m_maxReconnTimes, m_reconnectTimes->text().toInt());

		updateReconnConfig();

		respCancel();
	}

	void LoginPage::respCancel()
	{
		m_animation.addAnimation(m_systemWidget, QRect(QPoint(0, m_loginWidget->height()), m_loginWidget->size()), [&]() {
			m_systemWidget->hide();
		});
	}

	void LoginPage::showRegistWindow()
	{
		m_registWidget->setGeometry(QRect(QPoint(0, m_loginWidget->height()), m_loginWidget->size()));
		m_animation.addAnimation(m_registWidget, QRect(QPoint(0, 0), m_loginWidget->size()), [&]() {
			m_loginModel = false;
		});
		m_registWidget->show();
	}

	void LoginPage::respRegist()
	{
		if (m_registPassword1->text().isEmpty() || m_registPassword1->text().isEmpty()) {
			Util::showWarning(this, QStringLiteral("����Ϊ�գ���������д!"));
			return;
		}

		if (m_registPassword1->text() != m_registPassword2->text()) {
			Util::showWarning(this, QStringLiteral("�������벻һ�£���������д!"));
			return;
		}

		connectToServer();
	}

	void LoginPage::respCancelRegist()
	{
		m_animation.addAnimation(m_registWidget, QRect(QPoint(0, m_loginWidget->height()), m_loginWidget->size()), [&]() {
			clearRegistInput();

			m_loginModel = true;

			m_registWidget->hide();
		});
	}

	void LoginPage::init()
	{
		QWidget * mainWidget = new QWidget();
		mainWidget->setObjectName("Widget_LoginBackGround");

		m_loginWidget = new QWidget();
		m_loginWidget->installEventFilter(this);

		QLabel * titleLabel = new QLabel();
		titleLabel->setObjectName("Label_Login_TitleLabel");
		titleLabel->setAlignment(Qt::AlignCenter);
		titleLabel->setFixedHeight(30);
		titleLabel->setText(QStringLiteral("ϵͳ�˻���¼"));

		m_userName = new QLineEdit();
		m_userName->setMinimumHeight(25);
		m_userName->setPlaceholderText(QStringLiteral("�������û���"));
		m_userName->setText("root");

		m_password = new QLineEdit();
		m_password->setEchoMode(QLineEdit::Password);
		m_password->setMinimumHeight(25);
		m_password->setPlaceholderText(QStringLiteral("����������"));
		m_password->setText("1234");

		m_loginButt = new Base::RIconButton();
		m_loginButt->setIconSize(Base::RIconButton::ICON_24);
		m_loginButt->setIcon(QIcon(WRAP_RESOURCE(��¼)));
		m_loginButt->setText(QStringLiteral("��¼"));
		connect(m_loginButt, SIGNAL(clicked()), this, SLOT(connectToServer()));

		m_userRegistSetting = new Base::RIconButton(m_loginWidget);
		m_userRegistSetting->disableColors(Base::RIconButton::Color_All);
		m_userRegistSetting->enableColors(Base::RIconButton::Color_NormalText, Qt::white);
		m_userRegistSetting->enableColors(Base::RIconButton::Color_HoverText, Qt::red);
		m_userRegistSetting->setText(QStringLiteral("ע���˺�"));
		connect(m_userRegistSetting, SIGNAL(clicked()), this, SLOT(showRegistWindow()));


		m_systemSetting = new Base::RIconButton(m_loginWidget);
		m_systemSetting->disableColors(Base::RIconButton::Color_All);
		m_systemSetting->enableColors(Base::RIconButton::Color_NormalText, Qt::white);
		m_systemSetting->enableColors(Base::RIconButton::Color_HoverText, Qt::red);
		m_systemSetting->setText(QStringLiteral("ϵͳ����"));
		connect(m_systemSetting, SIGNAL(clicked()), this, SLOT(showSystemSetting()));

		QVBoxLayout * vlayout = new QVBoxLayout();
		vlayout->addWidget(titleLabel);
		vlayout->addWidget(m_userName);
		vlayout->addWidget(m_password);
		vlayout->addWidget(m_loginButt);

		m_loginWidget->setLayout(vlayout);

		int fixedWidth = 80;
		auto createLabel = [&](QString text) {
			QLabel * label = new QLabel();
			label->setFixedWidth(fixedWidth);
			label->setText(text);
			label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
			return label;
		};

		QSize fixSize(70, 25);
		auto createButton = [&](QString text, const char * pslot) {
			Base::RIconButton * butt = new Base::RIconButton();
			butt->setText(text);
			butt->setFixedSize(fixSize);
			connect(butt, SIGNAL(clicked()), this, pslot);
			return butt;
		};

		//ϵͳ����ҳ��
		{
			m_systemWidget = new QWidget(m_loginWidget);
			m_systemWidget->setStyleSheet("background-color:rgba(0,77,136, 230)");

			QLabel * remoteIp = createLabel(QStringLiteral("��������ַ:"));
			QLabel * remoteDataPort = createLabel(QStringLiteral("���ݶ˿ں�:"));
			QLabel * remoteFilePort = createLabel(QStringLiteral("�ļ��˿ں�:"));
			QLabel * netreConnLabel = createLabel(QStringLiteral("��������:"));

			m_ipWidget = new Base::RIPWidget();
			m_dataPortWidget = new QLineEdit();
			m_filePortWidget = new QLineEdit();

			m_autoReconnet = new QCheckBox();

			QLabel * maxTimes = createLabel(QStringLiteral("�����������:"));
			m_reconnectTimes = new QLineEdit();
			m_reconnectTimes->setMinimumWidth(80);
			m_reconnectTimes->setMinimumHeight(25);

			connect(m_autoReconnet, SIGNAL(toggled(bool)),m_reconnectTimes,SLOT(setEnabled(bool)));

			QHBoxLayout * netLayout = new QHBoxLayout();
			netLayout->addWidget(m_autoReconnet);
			netLayout->addWidget(maxTimes);
			netLayout->addWidget(m_reconnectTimes);
			netLayout->addStretch(1);
			netLayout->addSpacing(10);

			Base::RIconButton * saveButt = createButton(QStringLiteral("����"), SLOT(respSave()));
			Base::RIconButton * cancelButt = createButton(QStringLiteral("ȡ��"), SLOT(respCancel()));

			QWidget * toolContainer = new QWidget();
			toolContainer->setMinimumHeight(40);
			QHBoxLayout * toolLayout = new QHBoxLayout();
			toolLayout->addStretch(1);
			toolLayout->addWidget(saveButt);
			toolLayout->addWidget(cancelButt);
			toolLayout->addStretch(1);
			toolContainer->setLayout(toolLayout);

			QGridLayout * slayout = new QGridLayout();
			slayout->setVerticalSpacing(15);

			slayout->setRowStretch(0, 1);
			slayout->addWidget(remoteIp, 1, 0, 1, 1);
			slayout->addWidget(m_ipWidget, 1, 1, 1, 1);
			slayout->addWidget(remoteDataPort, 2, 0, 1, 1);
			slayout->addWidget(m_dataPortWidget, 2, 1, 1, 1);
			slayout->addWidget(remoteFilePort, 3, 0, 1, 1);
			slayout->addWidget(m_filePortWidget, 3, 1, 1, 1);
			slayout->addWidget(netreConnLabel, 4, 0, 1, 1);
			slayout->addLayout(netLayout, 4, 1, 1, 1);
			slayout->setRowStretch(5, 1);

			slayout->addWidget(toolContainer, 6, 0, 1, 2);

			m_systemWidget->setLayout(slayout);
			m_systemWidget->hide();
		}

		//�û�ע��ҳ��
		{
			m_registWidget = new QWidget(m_loginWidget);
			m_registWidget->setStyleSheet("background-color:rgba(0,77,136, 230)");

			QLabel * registUserName = createLabel(QStringLiteral("�û���:"));
			QLabel * password1 = createLabel(QStringLiteral("����:"));
			QLabel * password2 = createLabel(QStringLiteral("ȷ������:"));

			m_registUserName = new QLineEdit();

			m_registPassword1 = new QLineEdit();
			m_registPassword1->setEchoMode(QLineEdit::Password);

			m_registPassword2 = new QLineEdit();
			m_registPassword2->setEchoMode(QLineEdit::Password);

			Base::RIconButton * registButt = createButton(QStringLiteral("ע��"), SLOT(respRegist()));
			Base::RIconButton * cancelButt = createButton(QStringLiteral("ȡ��"), SLOT(respCancelRegist()));

			QWidget * toolContainer = new QWidget();
			toolContainer->setMinimumHeight(40);
			QHBoxLayout * toolLayout = new QHBoxLayout();
			toolLayout->addStretch(1);
			toolLayout->addWidget(registButt);
			toolLayout->addWidget(cancelButt);
			toolLayout->addStretch(1);
			toolContainer->setLayout(toolLayout);

			QGridLayout * slayout = new QGridLayout();
			slayout->setVerticalSpacing(15);

			slayout->setRowStretch(0, 1);
			slayout->addWidget(registUserName, 1, 0, 1, 1);
			slayout->addWidget(m_registUserName, 1, 1, 1, 1);
			slayout->addWidget(password1, 2, 0, 1, 1);
			slayout->addWidget(m_registPassword1, 2, 1, 1, 1);
			slayout->addWidget(password2, 3, 0, 1, 1);
			slayout->addWidget(m_registPassword2, 3, 1, 1, 1);
			slayout->setRowStretch(4, 1);

			slayout->addWidget(toolContainer, 5, 0, 1, 2);

			m_registWidget->setLayout(slayout);
			m_registWidget->hide();
		}

		m_container = new CustomWidgetContainer(mainWidget);
		m_container->setFixedSize(360, 420);
		m_container->setContent(m_loginWidget);
		m_container->show();

		QHBoxLayout * layout = new QHBoxLayout();
		layout->setContentsMargins(0, 0, 0, 0);
		layout->addWidget(mainWidget);
		setLayout(layout);
	}

	void LoginPage::initConnect()
	{
		connect(ConnectorManage::instance(), SIGNAL(connectResult(Datastruct::ConnectionType, bool, QString)), this, SLOT(respConnectResult(Datastruct::ConnectionType, bool, QString)));
		connect(ConnectorManage::instance(), SIGNAL(reconnResult(Datastruct::ConnectionType, int)), this, SLOT(respReconnResult(Datastruct::ConnectionType,int)));
		connect(SignalDispatch::instance(), SIGNAL(respUserLoginResponse(const Datastruct::UserLoginResponse &)), this, SLOT(processUserLoginResponse(const Datastruct::UserLoginResponse &)));
		connect(SignalDispatch::instance(), SIGNAL(respUserRegistResponse(const Datastruct::UserRegistResponse &)), this, SLOT(processUserRegistResponse(const Datastruct::UserRegistResponse &)));
	}

	void LoginPage::loadNetConfig()
	{
		ConfigKey ckey;

		m_ipWidget->setIP(Base::RUtil::getGlobalValue(ckey.m_netGroupId, ckey.m_remoteServerIp, "127.0.0.1").toString());
		m_dataPortWidget->setText(Base::RUtil::getGlobalValue(ckey.m_netGroupId, ckey.m_remoteServerDataPort, "8888").toString());
		m_filePortWidget->setText(Base::RUtil::getGlobalValue(ckey.m_netGroupId, ckey.m_remoteServerFilePort, "9999").toString());
		m_autoReconnet->setChecked(Base::RUtil::getGlobalValue(ckey.m_netGroupId, ckey.m_netAutoReconnect, true).toBool());
		m_reconnectTimes->setText(Base::RUtil::getGlobalValue(ckey.m_netGroupId, ckey.m_maxReconnTimes, 5).toString());
	}

	void LoginPage::updateReconnConfig()
	{
		ConnectorManage::instance()->setNetAutoConnect(m_autoReconnet->isChecked(), m_reconnectTimes->text().toInt());
	}

	void LoginPage::clearRegistInput()
	{
		m_registUserName->clear();
		m_registPassword1->clear();
		m_registPassword2->clear();
	}

} //namespace Related 