#pragma once
#include "base/enum.h"
#include "base/math/Size.h"
#include "qcolor.h"
#include "qnamespace.h"
#include "qwidget.h"

namespace widget
{
	///
	/// @brief 指示灯控件。
	///
	///
	class IndicatorLight :
		public QWidget
	{
	private:
		base::Enum::SwitchState _state = base::Enum::SwitchState::Off;
		QColor _on_color = Qt::GlobalColor::green;
		QColor _off_color = Qt::GlobalColor::gray;

	protected:
		virtual void paintEvent(QPaintEvent *) override;

	public:
		///
		/// @brief 构造默认指示灯。
		/// 	@li 打开状态是绿色，关闭状态是灰色。
		/// 	@li 初始时处于关闭状态。
		/// 	@li 大小为 20px * 20px.
		///
		///
		IndicatorLight();

		IndicatorLight(base::Size const &size, QColor on_color, QColor off_color);

		IndicatorLight(base::Size const &size,
					   base::Enum::SwitchState initial_state,
					   QColor on_color,
					   QColor off_color);

		///
		/// @brief 指示灯当前的开关状态。
		///
		/// @return base::Enum::SwitchState
		///
		base::Enum::SwitchState State() const;

		///
		/// @brief 设置指示灯的开关状态。
		///
		/// @param value
		///
		void SetState(base::Enum::SwitchState value);

		///
		/// @brief 指示灯打开时的颜色。
		///
		/// @return QColor
		///
		QColor OnColor() const;

		///
		/// @brief 设置指示灯打开时的颜色。
		///
		/// @param value
		///
		void SetOnColor(QColor value);

		///
		/// @brief 指示灯关闭时的颜色。
		///
		/// @return QColor
		///
		QColor OffColor() const;

		///
		/// @brief 设置指示灯关闭时的颜色。
		///
		/// @param value
		///
		void SetOffColor(QColor value);

		///
		/// @brief 指示灯当前的颜色。
		///
		/// @return QColor
		///
		QColor CurrentColor() const;
	};
} // namespace widget
