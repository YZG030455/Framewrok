/*!
 *  @brief     ���ݷ���ҳ��
 *  @details   1.�ṩ¼�����Լ���Ƶ�༭��ز�����
			   2.�ṩ��Ƶ���������������������ߵȣ�
 *  @author    wey
 *  @version   1.0
 *  @date      2021.01.07
 *  @warning
 *  @copyright NanJing RenGu.
 *  @note
 */
#pragma once

#include <QWidget>
#include <QStackedWidget>
#include <QVBoxLayout>

#include <base\selfwidget\rtabbar.h>
#include "../abstractpage.h"

#include "DemonSpectrogramWidget.h"
#include "gatherwidget.h"
#include "inspectwidget.h"

namespace Related {

	class DataAnalyseWidget : public AbstractPage
	{
		Q_OBJECT

	public:
		DataAnalyseWidget(QWidget *parent = nullptr);
		~DataAnalyseWidget();

		PageType getPageType() const;

	private slots:
		void slotDataGather();
		void slotSignalOut();
		void slotInspectSignalOut();
	private:
		void init();

	private:
		QStackedWidget *m_stackedWidget;
	};

}//namespace Related 