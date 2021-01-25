#pragma once

#include <QWidget>

#include "../datastruct.h"

namespace Related {

	class AbstractPage : public QWidget
	{
		Q_OBJECT

	public:
		AbstractPage(QWidget *parent);
		~AbstractPage();

		virtual PageType getPageType() const = 0;

		/*!
		 * @brief ҳ�潫���л������ϲ���ʾ
		 * @details ����������ҳ���һ�γ�ʼ���Ȼص�
		 */
		virtual void prepareBringToTop() {}

		/*!
		 * @brief ҳ�潫���л�������ʾ״̬
		 * @details ���������ر�δ������Ĳ���
		 */
		virtual void prepareBringToBottom() {}

	};

} //namespace Related 