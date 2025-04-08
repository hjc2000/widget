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
		virtual void paintEvent(QPaintEvent *event) override;

	public:
		/* #region 构造函数 */

		///
		/// @brief 构造默认指示灯。
		/// 	@li 打开状态是绿色，关闭状态是灰色。
		/// 	@li 初始状态为关闭。
		/// 	@li 大小为 24px * 24px.
		///
		///
		IndicatorLight();

		///
		/// @brief 构造指示灯。
		/// 	@li 初始状态为关闭。
		/// 	@li 大小为 24px * 24px.
		///
		/// @param on_color 指示灯开启时的颜色。
		/// @param off_color 指示灯关闭时的颜色。
		///
		IndicatorLight(QColor on_color, QColor off_color);

		///
		/// @brief 构造指示灯。
		/// 	@note 初始状态为关闭。
		///
		/// @param size 指示灯大小。
		/// @param on_color 指示灯开启时的颜色。
		/// @param off_color 指示灯关闭时的颜色。
		///
		IndicatorLight(base::Size const &size, QColor on_color, QColor off_color);

		///
		/// @brief 构造指示灯。
		///
		/// @param size 指示灯大小。
		/// @param initial_state
		/// @param on_color 指示灯开启时的颜色。
		/// @param off_color 指示灯关闭时的颜色。
		///
		IndicatorLight(base::Size const &size,
					   base::Enum::SwitchState initial_state,
					   QColor on_color,
					   QColor off_color);

		/* #endregion */

		/* #region 属性 */

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

		/* #endregion */
	};
} // namespace widget
