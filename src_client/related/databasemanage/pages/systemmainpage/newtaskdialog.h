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
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QFileDialog>
#include <QStackedWidget>
#include <QDir>
#include <QDateTime>

#include <base/selfwidget/dialogproxy.h>
#include <base/selfwidget/treemode/rtreeview.h>
#include <base/selfwidget/treemode/rtreemodel.h>
#include <base/selfwidget/iconbutton.h>
#include <base/selfwidget/rtabbar.h>
#include <base/selfwidget/rtabwidget.h>
#include <base\selfwidget\rmessagebox.h>
#include <base/util/rutil.h>

#include <commondefines/protocol.h>

#include "controlwidget/newtaskinfosetwidget.h"

namespace Related {

	class NewTaskDialog : public Base::DialogProxy
	{
		Q_OBJECT

	public:
		NewTaskDialog(QWidget *parent = nullptr);
		~NewTaskDialog();

	private slots:
		void slotSeleteFile();
		void slotTreeItemClicked(QModelIndex index);
		void respOk();
		void respCancel();

	private:
		void init();
		bool FindFile(const QString &path);
		Base::TreeNode * createTreeNode(Base::TreeNode * parentNode, QString  pasth);
		void updateModel();
		bool getFileNode(Base::TreeNode *node);

		void sendTaskBaseInfo();
		void sendTaskOriginalDataInfo();

	private:
		enum TabIndex {
			TabBaseInfo,		/*!< ������Ϣ */
			TabImage,			/*!< ͼƬ��Ϣ */
			TabData				/*!< ������Ϣ */
		};

	private:
		TaskBaseInfo m_taskBaseInfo;					/*!< ���������Ϣ */
		NewTaskInfoSetWidget * m_newTaskWidget;			/*!< �½��������ý��� */

		//�ļ���
		Base::RTreeView * m_treeView;					
		Base::RTreeModel * m_treeModel;
		Base::TreeNode * m_fileRootNode;				/*! <�ļ������ڵ�> */	

		Base::RTabWidget * m_tabWidget;

		QLineEdit * m_fileLineEdit;
		Base::RIconButton * m_fileButt;
		QString m_originalFilePath;						/*!< ԭʼ�ļ�·��������·�� */

		QList<OriginalDataFileParameter *> m_taskDataFilePaths;
	};

}//namespace Related 