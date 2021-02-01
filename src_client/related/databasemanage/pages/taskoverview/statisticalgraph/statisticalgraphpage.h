/*!
 * @brief     ����ͼͳ��ҳ��
 * @details   ���Ʋ���ʾ���ͽṹͼ
 * @author    yzg
 * @version   1.0
 * @date      2021.01.21 17:12:04
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

//[]
#include <QtCharts>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QChartView>


namespace Related {

	class StatisticalGraphPage : public QWidget
	{
		Q_OBJECT

	public:
		StatisticalGraphPage(QWidget *parent = nullptr);
		~StatisticalGraphPage();
		
		void init();

	private:
		QChartView *m_chartView;
		QChart *m_chart;

	};
}//namespace Related 
