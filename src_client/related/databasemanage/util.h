/*!
 * @brief     ������
 * @details	  �ṩ�뵱ǰ������صĹ��߲�����
 * @author    wey
 * @version   1.0
 * @date      21.01.14 14:54:25
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
#pragma once

#include <QObject>

#include <base\selfwidget\iconbutton.h>

namespace Related {

	class Util : public QObject
	{
	public:
		Util(QObject *parent = nullptr);
		~Util();

		static Base::RIconButton * createButt(QString icon, QString text);
	};

} //namespace Related 