/*!
 *  @brief     ���ݸ�����ʾҳ��
 *  @details   ��ʾ��ǰ���ݿ��Ҫ��Ϣ��ͨ��ͼ������鼯��չʾ��
 *  @author    wey
 *  @version   1.0
 *  @date      2021.01.07
 *  @warning
 *  @copyright NanJing RenGu.
 *  @note
 */
#pragma once

#include <QWidget>

#include "overviewitem.h"
#include "../abstractpage.h"
#include "../../3rdLibrary/qcustomplot.h"

namespace Related {

	class MainPage : public AbstractPage
	{
		Q_OBJECT

	public:
		MainPage(QWidget *parent = nullptr);
		~MainPage();

		PageType getPageType() const;

	private:
		void init();
		void initPlot(QCustomPlot * plot);

	private:
		OverViewItem * m_todayAddItem;
		OverViewItem * m_totalItem;
		OverViewItem * m_unprocessItem;
	};

} //namespace Related