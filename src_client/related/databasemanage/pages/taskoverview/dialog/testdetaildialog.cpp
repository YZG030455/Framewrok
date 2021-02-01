#include "testdetaildialog.h"

#include <QDebug>

namespace Related {

	TestDetailDialog::TestDetailDialog(QWidget *parent)
		: Base::DialogProxy(parent)
	{

		setTitle(QStringLiteral("�½�����"));
		setMinimumSize(900, 650);

		setButton(DialogProxy::Ok, this, SLOT(respOk()));
		setButton(DialogProxy::Cancel, this, SLOT(reject()));

		init();
	}

	TestDetailDialog::~TestDetailDialog()
	{
	}

	void TestDetailDialog::init()
	{
	}

}//namespace Related 