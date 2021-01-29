/*!
 * @brief     �½��������
 *  @details  �������������Ϣ�����ϴ��ļ�
 * @author    yzg
 * @version   1.0
 * @date      2021.01.22 18:32:39
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QFileSystemModel>
#include <QScrollArea>
#include <QTreeView>

#include <base/selfwidget/dialogproxy.h>
#include <base\selfwidget\tablemode\rtableview.h>
#include <base/selfwidget/iconbutton.h>
#include <base/selfwidget/rtabwidget.h>
#include <base\selfwidget\rmessagebox.h>
#include <base/util/rutil.h>

#include <commondefines/protocol.h>

#include "controlwidget/newtaskinfosetwidget.h"
#include "controlwidget/imagemodel.h"

namespace Related {

	class NewTaskDialog : public Base::DialogProxy
	{
		Q_OBJECT

	public:
		NewTaskDialog(QWidget *parent = nullptr);
		~NewTaskDialog();

	private slots:
		void respOk();
		void openLocalImage();
		void clearImage();
		void processTaskCreateResponse(const Datastruct::TaskCreateResponse & response);
	private:
		void init();
		void initConnect();

		void sendTaskBaseInfo();

	private:
		Base::RTabWidget * m_tabWidget;

		TaskBaseInfo m_taskBaseInfo;					/*!< ���������Ϣ */
		NewTaskInfoSetWidget * m_newTaskWidget;			/*!< �½��������ý��� */

		Base::RTableView * m_tableView;
		ImageModel * m_imageTableModel;
		Base::RIconButton * m_viewModelSwitch;

		QScrollArea * m_cardModel;

		QStackedWidget * m_imageStack;

		Base::RTableView * m_fileTableView;
		ImageModel * m_fileTableModel;

		QLineEdit * m_dataFilePath;						/*!< �����ļ�·�� */

		QString m_originalFilePath;						/*!< ԭʼ�ļ�·��������·�� */

		QList<OriginalDataFileParameter *> m_taskDataFilePaths;
	};

}//namespace Related 