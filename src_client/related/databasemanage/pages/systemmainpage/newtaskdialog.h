/*!
 * @brief     新建任务界面
 *  @details  设置任务基本信息，并上传文件
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
		void slotSeleteFile();
		void respOk();
		void respCancel();

		void openLocalImage();
		void clearImage();

	private:
		void init();

		void sendTaskBaseInfo();

	private:
		Base::RTabWidget * m_tabWidget;

		TaskBaseInfo m_taskBaseInfo;					/*!< 任务基本信息 */
		NewTaskInfoSetWidget * m_newTaskWidget;			/*!< 新建任务设置界面 */

		Base::RTableView * m_tableView;
		ImageModel * m_imageTableModel;

		QTreeView * m_treeView;
		QFileSystemModel * m_treeModel;

		QLineEdit * m_dataFilePath;						/*!< 数据文件路径 */

		QString m_originalFilePath;						/*!< 原始文件路径：绝对路径 */

		QList<OriginalDataFileParameter *> m_taskDataFilePaths;
	};

}//namespace Related 