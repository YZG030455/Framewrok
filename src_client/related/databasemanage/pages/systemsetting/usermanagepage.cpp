#include "usermanagepage.h"

#include <QHBoxLayout>
#include <QGridLayout>
#include <QItemSelectionModel>
#include <QDebug>
#include <QHBoxLayout>

#include <commondefines/protocol.h>
#include <base/selfwidget/rmessagebox.h>

#include "../utils/util.h"
#include "../customwidget/pageswitchbar.h"
#include "../customwidget/customwidgetcontainer.h"
#include "../net/netconnector.h"
#include "../net/signaldispatch.h"
#include "../global.h"
#include "userprivilegeeditwindow.h"

namespace Related {

	UserManagePage::UserManagePage(QWidget *parent)
		: AbstractPage(parent), m_firstLoadData(true)
	{
		init();

		connect(SignalDispatch::instance(), SIGNAL(respQueryUserListResponse(const Datastruct::LoadAllUserResponse &)),
			this, SLOT(respQueryUserListResponse(const Datastruct::LoadAllUserResponse &)));

		connect(SignalDispatch::instance(), SIGNAL(resOperateUserResponse(const Datastruct::OperateUserResponse &)),
			this, SLOT(resOperateUserResponse(const Datastruct::OperateUserResponse &)));
	}

	UserManagePage::~UserManagePage()
	{
	}

	PageType UserManagePage::getPageType() const
	{
		return Page_Setting_UserManage;
	}

	void UserManagePage::prepareBringToTop()
	{
		if (Global::G_UserEntity.isManager) {
			if (m_firstLoadData) {
				refreshCurrPage();
				m_firstLoadData = false;
			}
			m_contentWidget->setCurrentIndex(0);
		}
		else {
			m_contentWidget->setCurrentIndex(1);
		}
	}

	void UserManagePage::setPageNum(int page)
	{
		refreshCurrPage();
	}

	/*!
	 * @brief �����û��б�����ѯ����
	 * @param response �û��б��ѯ���
	 */
	void UserManagePage::respQueryUserListResponse(const Datastruct::LoadAllUserResponse & response)
	{
		m_tableModel->updateData(response.m_userInfos);
		m_pageSwitch->setDataSize(response.m_userCount);
	}

	/*!
	 * @brief �����û��������
	 * @param response �û������������
	 */
	void UserManagePage::resOperateUserResponse(const Datastruct::OperateUserResponse & response)
	{
		switch (response.m_operateType)
		{
			case Datastruct::UpdateInfo: {

			}
				break;
			case Datastruct::EditPrivilege: {
				if (response.m_operateResult) {
					Util::showInformation(this, QStringLiteral("Ȩ�޸��³ɹ�!"));
					refreshCurrPage();
				}
				else {
					Util::showWarning(this, Datastruct::G_StrError(response.m_errorCode));
				}
			}
				break;
			case Datastruct::DeleteUser: {
				if (response.m_operateResult) {
					Util::showInformation(this, QStringLiteral("ɾ���ɹ�!"));
					refreshCurrPage();
				}
				else {
					Util::showWarning(this, Datastruct::G_StrError(response.m_errorCode));
				}
			}
				break;
			default:
				break;
		}
	}

	void UserManagePage::respToolButtPressed(OperationToolsPage::ButtType type)
	{
		switch (type)
		{
			case OperationToolsPage::Butt_Delete: 
			case OperationToolsPage::Butt_Edit: {

				QItemSelectionModel * selectModel = m_tableView->selectionModel();
				QModelIndexList slist = selectModel->selectedRows();
				if (slist.size() > 0) {
					int selectedRow = slist.at(0).row();

					if (selectedRow > m_tableModel->datasSize()) {
						Util::showWarning(this, QStringLiteral("δѡ������!"));
						return;
					}

					int dbIndex = m_tableModel->getRecordDatabaseIndex(selectedRow);
					if (dbIndex < 0) {
						Util::showWarning(this, QStringLiteral("��ȡ���ݿ�����ʧ��!"));
						return;
					}

					if (type == OperationToolsPage::Butt_Delete) {
						if (Global::G_UserEntity.id == dbIndex) {
							Util::showWarning(this, QStringLiteral("����ɾ������!"));
							return;
						}

						Base::RMessageBox::StandardButton butt = Util::showQuestion(this, QStringLiteral("�Ƿ�ɾ��ѡ�м�¼?"));
						if (butt == Base::RMessageBox::Yes) {
							Datastruct::OperateUserRequest request;
							request.m_operateType = Datastruct::DeleteUser;
							request.m_id = dbIndex;
							request.m_manageId = Global::G_UserEntity.id;

							NetConnector::instance()->write(request);
						}
					}
					else if (type == OperationToolsPage::Butt_Edit) {
						if (Global::G_UserEntity.id == dbIndex) {
							Util::showWarning(this, QStringLiteral("���ܱ༭����!"));
							return;
						}

						UserPrivilegeEditWindow editWindow(this);

						editWindow.setInitUserPrivilege(m_tableModel->getUserPrivilege(selectedRow), m_tableModel->isUserManage(selectedRow));

						if (QDialog::Accepted == editWindow.exec()) {
							Datastruct::OperateUserRequest request;
							request.m_operateType = Datastruct::EditPrivilege;
							request.m_id = dbIndex;
							request.m_privilege = editWindow.getUserPrivilege();
							request.m_isManage = editWindow.getUserManage();
							request.m_manageId = Global::G_UserEntity.id;

							NetConnector::instance()->write(request);
						}
					}					
				}
			}
				break;
			case OperationToolsPage::Butt_Refresh: {
				refreshCurrPage();
			}
				break;
			default:
				break;
		}
	}

	void UserManagePage::setFixedPageRowCount(int pageItemCount)
	{
		m_tableModel->setFixedPageRowCount(pageItemCount);
	}

	void UserManagePage::init()
	{
		QWidget * tableManage = new QWidget();
		{
			m_operationToolsPage = new OperationToolsPage();
			m_operationToolsPage->setButtVisible(OperationToolsPage::Butt_Add, false);
			connect(m_operationToolsPage, SIGNAL(buttPressed(OperationToolsPage::ButtType)), this, SLOT(respToolButtPressed(OperationToolsPage::ButtType)));

			m_tableView = new Base::RTableView();
			m_tableView->setFocusPolicy(Qt::NoFocus);
			m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
			m_tableView->setSelectionMode(QAbstractItemView::SingleSelection);

			m_tableModel = new UserManageModel();

			m_tableView->setModel(m_tableModel);

			m_tableView->addColumnItem(Base::ColumnItem(U_Id, QStringLiteral("���")));
			m_tableView->addColumnItem(Base::ColumnItem(U_UserName, QStringLiteral("�û���"), 150));
			m_tableView->addColumnItem(Base::ColumnItem(U_RegisterTime, QStringLiteral("ע��ʱ��"), 260));
			m_tableView->addColumnItem(Base::ColumnItem(U_LastLoginTime, QStringLiteral("�ϴε�¼ʱ��"), 260));
			m_tableView->addColumnItem(Base::ColumnItem(U_UserRights, QStringLiteral("Ȩ��"),280));
			m_tableView->addColumnItem(Base::ColumnItem(U_IsManage, QStringLiteral("�Ƿ����Ա")));

			m_pageSwitch = new PageSwitchBar();
			connect(m_pageSwitch, SIGNAL(perPageNumsChanged(int)), this, SLOT(setFixedPageRowCount(int)));
			connect(m_pageSwitch, SIGNAL(switchPage(int)), this, SLOT(setPageNum(int)));

			CustomWidgetContainer * cwidget = new CustomWidgetContainer();
			cwidget->setContent(m_operationToolsPage);

			QWidget * twidget = new QWidget();
			QVBoxLayout * cvlayout = new QVBoxLayout();
			cvlayout->setContentsMargins(0, 0, 0, 0);
			cvlayout->addWidget(m_tableView);
			cvlayout->addWidget(m_pageSwitch);
			twidget->setLayout(cvlayout);

			CustomWidgetContainer * ctableView = new CustomWidgetContainer();
			ctableView->setContent(twidget);

			QVBoxLayout * vlayout = new QVBoxLayout();
			vlayout->setContentsMargins(4, 4, 4, 4);
			vlayout->addWidget(cwidget);
			vlayout->addWidget(ctableView);

			tableManage->setLayout(vlayout);
		}

		QWidget * privilegeWidget = new QWidget();
		{
			QLabel * iconLabel = new QLabel();
			iconLabel->setAlignment(Qt::AlignCenter);
			iconLabel->setPixmap(QPixmap(QStringLiteral(":/QYBlue/resource/qyblue/Ȩ��.png")));

			QLabel * textLabel = new QLabel();
			textLabel->setText(QStringLiteral("�޷���Ȩ��!"));
			textLabel->setStyleSheet("font-size:18px;");

			QGridLayout * glayout = new QGridLayout();
			glayout->setRowStretch(0, 1);
			glayout->setColumnStretch(0, 1);

			glayout->addWidget(iconLabel, 1, 1, 1, 1);
			glayout->addWidget(textLabel, 2, 1, 1, 1);

			glayout->setColumnStretch(2, 1);
			glayout->setRowStretch(3, 1);

			glayout->setVerticalSpacing(12);

			privilegeWidget->setLayout(glayout);
		}

		m_contentWidget = new QStackedWidget();
		m_contentWidget->addWidget(tableManage);
		m_contentWidget->addWidget(privilegeWidget);

		QVBoxLayout * layout = new QVBoxLayout();
		layout->setContentsMargins(0, 0, 0, 0);
		layout->addWidget(m_contentWidget);
		setLayout(layout);
	}

	/*!
	 * @brief ˢ�µ�ǰҳ������
	 * @details ҳ���л�����ʾ�����л��ȸı�ʱ�����ô˷����ɻ�ü�ʱˢ��
	 */
	void UserManagePage::refreshCurrPage()
	{
		Datastruct::LoadAllUserRequest request;
		request.m_name = Global::G_UserEntity.name;
		request.m_offsetIndex = m_pageSwitch->dataOffset();
		request.m_limitIndex = m_pageSwitch->perPageCount();
		NetConnector::instance()->write(request);
	}

}//namespace Related 