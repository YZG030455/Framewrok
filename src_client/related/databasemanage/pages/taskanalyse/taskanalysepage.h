/*!
 * @brief     �������ҳ��  
 * @author    wey
 * @version   1.0
 * @date      2021.01.20 09:18:29
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */

 #pragma once

#include <QWidget>
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>


#include <base\selfwidget\rtabbar.h>
#include "../abstractpage.h"

#include "dataoverviewwidget.h"
#include "audiodatawidget.h"
#include "ambientnoisedatawidget.h"
#include "hxjplatforminfowidget.h"

namespace Related {

	class TaskAnalysePage : public AbstractPage
	{
		Q_OBJECT

	public:
		TaskAnalysePage(QWidget *parent = nullptr);
		~TaskAnalysePage();

		PageType getPageType() const;

		enum TaskAnalyseIndex
		{
			Tab_dataOverview,			/*!<  ���ݸ������� */
			Tab_advInfo,				/*!< ��Ƶ��Ϣ���� */
			Tab_ambientNoise,			/*!< ������������ */
			Tab_hxjInfo,				/*!< HXJƽ̨���� */
		};

	private slots:
		void respTabChanged(int page);

	private:
		void init();

	private:
		Base::RTabBar * m_tabWidget;
		QStackedWidget * m_stackedWidget;

		DataOverviewWidget * m_dataOverviewWidget;			/*!< ������������ */
		AudioDataWidget * m_audioDataWidget;				/*!< ��Ƶ����չʾ���� */
		AmbientNoiseDataWidget * m_ambientNoiseDataWidget;	/*!< ������������չʾ���� */
		HXJPlatformInfoWidget * m_hxjPlatformDataWidget;	/*!< HXJƽ̨��Ϣչʾ���� */
	};

} //namespace Related 