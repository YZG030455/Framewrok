/*!
 * @brief     �����¼ҳ��
 * @details   �ṩֵ����¼�������¼��ҳ��
 * @author    wey
 * @version   1.0
 * @date      2021.01.20 09:16:07
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
 #pragma once

#include <QWidget>

#include "../abstractpage.h"

namespace Related {

	class TaskRecordPage : public AbstractPage
	{
		Q_OBJECT

	public:
		TaskRecordPage(QWidget *parent = nullptr);
		~TaskRecordPage();

		PageType getPageType() const;

	private:
		void init();
	};

} //namespace Related 