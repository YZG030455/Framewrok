/*!
 * @brief     ��Ƶʱ��������ͼ  
 * @details   1.��ʾ��ǰ����Ƶ�Ĳ���ͼ
			  2.֧��������ʾ��Χ�鿴
 * @author    wey
 * @version   1.0
 * @date      2021.02.01 17:08:25
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
 #pragma once

#include <QWidget>

namespace Related {

	class TinyWavGraph : public QWidget
	{
		Q_OBJECT

	public:
		TinyWavGraph(QWidget * parent = nullptr);
		~TinyWavGraph();

	protected:
		bool eventFilter(QObject * watched, QEvent * event);

	private:
		void init();

	private:
		QWidget * m_waveGraph;
	};

} //namespace Related 