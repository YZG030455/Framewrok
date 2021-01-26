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


#include <base\selfwidget\rtabwidget.h>
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

	private:
		void init();

	private:
		Base::RTabWidget * m_tabWidget;

		DataOverviewWidget * m_dataOverviewWidget;			/*!< ������������ */
		AudioDataWidget * m_audioDataWidget;				/*!< ��Ƶ����չʾ���� */
		AmbientNoiseDataWidget * m_ambientNoiseDataWidget;	/*!< ������������չʾ���� */
		HXJPlatformInfoWidget * m_hxjPlatformDataWidget;	/*!< HXJƽ̨��Ϣչʾ���� */
	};

} //namespace Related 