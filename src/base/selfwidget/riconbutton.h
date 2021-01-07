﻿/*!
 *  @brief     自定义按钮类
 *  @details   按钮格式为左边logo右边文字
 *  @author    byy
 *  @version   1.0
 *  @date      2020.09.12
 *  @warning
 *  @copyright NanJing RenGu.
 */
#ifndef MARSBUTTON_H
#define MARSBUTTON_H

#include <QAbstractButton>
#include "../base_global.h"

namespace Base {

	class BASESHARED_EXPORT MarsButton : public QAbstractButton
	{
		Q_OBJECT
	public:
		explicit MarsButton(QWidget *parent = 0);

		/*!
		 *  @brief 图标尺寸
		 */
		enum IconSize {
			ICON_16,
			ICON_24,
			ICON_32,
			ICON_48,
			ICON_64,
			ICON_custom
		};

		enum ColorChoose {
			Color_NormalBackGround = 0x0001,
			Color_CheckedBackGround = 0x0002,
			Color_HoverBackground = 0x0004,
			Color_NormalBorder = 0x0008,
			Color_CheckedBorder = 0x0010,
			Color_HoverBorder = 0x0020,
			Color_NormalText = 0x0040,
			Color_CheckedText = 0x0080,
			Color_HoverText = 0x0100,

			Color_All = Color_NormalBackGround | Color_CheckedBackGround | Color_HoverBackground | Color_NormalBorder | Color_CheckedBorder | Color_HoverBorder
			| Color_NormalText | Color_CheckedText | Color_HoverText
		};

		Q_DECLARE_FLAGS(ColorChooses, ColorChoose)

			void setCheckedIcon(const QIcon & icon);
		void setIconSize(IconSize type, QSize size = QSize());

		QSize sizeHint() const;
		QSize minimumSizeHint() const;

		void enableColor(ColorChoose choose, QColor color = QColor(255, 0, 0, 0));
		void disableColor(ColorChoose choose);

	protected:
		void paintEvent(QPaintEvent * event);
		void enterEvent(QEvent * event);
		void leaveEvent(QEvent * event);

	private:
		QSize calcMiniumSize() const;

		void updateColor(ColorChoose choose, QColor color);

		struct ColorCollect {
			QColor m_normalBackGroundColor;
			QColor m_checkedBackGroundColor;
			QColor m_hoverBackGroundColor;

			QColor m_normalBorderColor;
			QColor m_checkedBorderColor;
			QColor m_hoverBorderColor;

			QColor m_normalTextColor;
			QColor m_checkedTextColor;
			QColor m_hoverTextColor;
		};

	private:
		QSize m_iconSize;
		int m_spacing;                  /*!< 图标和文字之间的间隔 */

		QIcon m_checkedIcon;            /*!< 选中状态下图标 */

		bool m_mouseEnter;
		ColorChooses m_colorChoose;     /*!< 颜色开关 */
		QColor m_disableColor;          /*!< 无效的开关设置:默认为透明色 */

		ColorCollect m_colorCollect;
	};

} //namespace Base 

#endif // MARSBUTTON_H