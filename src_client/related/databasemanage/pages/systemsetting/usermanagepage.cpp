#include "usermanagepage.h"

#include <QHBoxLayout>
#include <QDebug>

#include <commondefines/protocol.h>
#include "../utils/util.h"
#include "../customwidget/pageswitchbar.h"
#include "../customwidget/customwidgetcontainer.h"
#include "../net/netconnector.h"
#include "../net/signaldispatch.h"
#include "../global.h"

namespace Related {

	UserManagePage::UserManagePage(QWidget *parent)
		: AbstractPage(parent), m_firstLoadData(true)
	{
		init();

		connect(SignalDispatch::instance(), SIGNAL(respQueryUserListResponse(const Datastruct::LoadAllUserResponse &)), 
			this, SLOT(respQueryUserListResponse(const Datastruct::LoadAllUserResponse &)));
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
		if (m_firstLoadData) {
			refreshCurrPage();
			m_firstLoadData = false;
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

	void UserManagePage::respToolButtPressed(OperationToolsPage::ButtType type)
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
		m_operationToolsPage = new OperationToolsPage();
		connect(m_operationToolsPage, SIGNAL(buttPressed(OperationToolsPage::ButtType)), this, SLOT(respToolButtPressed(OperationToolsPage::ButtType)));

		m_tableView = new Base::RTableView();
		m_tableView->setFocusPolicy(Qt::NoFocus);
		m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
		m_tableView->setSelectionMode(QAbstractItemView::SingleSelection);

		m_tableModel = new UserManageModel();

		m_tableView->setModel(m_tableModel);

		m_tableView->addColumnItem(Base::ColumnItem(U_Id, QStringLiteral("���")));
		m_tableView->addColumnItem(Base::ColumnItem(U_UserName, QStringLiteral("�û���"),140));
		m_tableView->addColumnItem(Base::ColumnItem(U_RegisterTime, QStringLiteral("ע��ʱ��"),180));
		m_tableView->addColumnItem(Base::ColumnItem(U_LastLoginTime, QStringLiteral("�ϴε�¼ʱ��"),180));
		m_tableView->addColumnItem(Base::ColumnItem(U_UserRights, QStringLiteral("Ȩ��")));

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
		setLayout(vlayout);
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