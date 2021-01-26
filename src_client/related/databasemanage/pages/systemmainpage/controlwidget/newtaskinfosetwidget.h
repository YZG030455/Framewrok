/*!
 * @brief     ���������Ϣ���ô���   
 * @author    yzg
 * @version   1.0
 * @date      2021.01.22 19:13:13
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "ui_newtaskinfosetwidget.h"

#include <base/util/rutil.h>

#include "taskpictureuploadwidget.h"
#include "../datastruct.h"

namespace Related {

	class NewTaskInfoSetWidget : public QWidget
	{
		Q_OBJECT

	public:
		NewTaskInfoSetWidget(QWidget *parent = Q_NULLPTR);
		~NewTaskInfoSetWidget();

		TaskBaseInfo getTaskBaseInfo();

	private slots:
		void slotPictureUploadPath(QString path);

	private:
		void init();

	private:
		Ui::NewTaskInfoSetWidget ui;
		TaskPictureUploadWidget * m_taskPictureUploadWidget;			/*!< ��������ͼƬ */
		TaskBaseInfo m_taskBaseInfo;									/*!< ���������Ϣ */
	};
}
