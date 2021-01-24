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
#include <QDir>

#include <base/selfwidget/dialogproxy.h>
#include <base/selfwidget/treemode/rtreeview.h>
#include <base/selfwidget/treemode/rtreemodel.h>
#include <base/selfwidget/iconbutton.h>

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

	private:
		NewTaskInfoSetWidget *m_newTaskInfoSetWidget;

		//�ļ���
		Base::RTreeView * m_treeView;
		Base::RTreeModel * m_treeModel;
		Base::TreeNode * m_fileNode;

		QLineEdit * m_fileLineEdit;
		Base::RIconButton * m_fileButt;
		QString m_originalFilePath;
	};

}//namespace Related 