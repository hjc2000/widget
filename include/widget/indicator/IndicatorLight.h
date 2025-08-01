#pragma once
#include "base/embedded/led/parameter.h"
#include "base/math/Size.h"
#include "qcolor.h"
#include "qnamespace.h"
#include "qpainter.h"
#include "qwidget.h"

namespace widget
{
	///
	/// @brief 指示灯控件。
	///
	///
	class IndicatorLight final :
		public QWidget
	{
	private:
		base::led::State _state = base::led::State::Off;
		QColor _on_color = Qt::GlobalColor::green;
		QColor _off_color = Qt::GlobalColor::gray;

	protected:
		virtual void paintEvent(QPaintEvent *event) override
		{
			QPainter painter{this};

			// 开启抗锯齿
			painter.setRenderHint(QPainter::Antialiasing);

			QColor color = CurrentColor();
			painter.setBrush(color);

			int border_width = 1;
			QPen pen{Qt::GlobalColor::black};
			pen.setWidth(border_width);
			painter.setPen(pen);

			// 调整绘图区域，避免边线超出控件范围。
			// 根据边线宽度调整
			//
			// 如果边线宽度不为 0，绘制边线一定会超出控件范围，导致虽然绘制的是圆形，看着是矩形。
			// 因为控件的视图窗口是矩形，超出范围的边线就看不见了，导致边线外围好像被用一个矩形
			// 模具切割。
			QRect adjustedRect = rect().adjusted(border_width, border_width, -border_width, -border_width);

			// 绘制圆形
			painter.drawEllipse(adjustedRect);
		}

	public:
		/* #region 构造函数 */

		///
		/// @brief 构造默认指示灯。
		/// 	@li 打开状态是绿色，关闭状态是灰色。
		/// 	@li 初始状态为关闭。
		/// 	@li 大小为 24px * 24px.
		///
		///
		IndicatorLight()
			: IndicatorLight(Qt::GlobalColor::green, Qt::GlobalColor::gray)
		{
		}

		///
		/// @brief 构造指示灯。
		/// 	@li 初始状态为关闭。
		/// 	@li 大小为 24px * 24px.
		///
		/// @param on_color 指示灯开启时的颜色。
		/// @param off_color 指示灯关闭时的颜色。
		///
		IndicatorLight(QColor on_color, QColor off_color)
			: IndicatorLight(base::Size{24, 24}, on_color, off_color)
		{
		}

		///
		/// @brief 构造指示灯。
		/// 	@note 初始状态为关闭。
		///
		/// @param size 指示灯大小。
		/// @param on_color 指示灯开启时的颜色。
		/// @param off_color 指示灯关闭时的颜色。
		///
		IndicatorLight(base::Size const &size, QColor on_color, QColor off_color)
			: IndicatorLight(size,
							 base::led::State::Off,
							 on_color,
							 off_color)
		{
		}

		///
		/// @brief 构造指示灯。
		///
		/// @param size 指示灯大小。
		/// @param initial_state
		/// @param on_color 指示灯开启时的颜色。
		/// @param off_color 指示灯关闭时的颜色。
		///
		IndicatorLight(base::Size const &size,
					   base::led::State initial_state,
					   QColor on_color,
					   QColor off_color)
		{
			setFixedSize(size.XSize(), size.YSize());
			_state = initial_state;
			_on_color = on_color;
			_off_color = off_color;
		}

		/* #endregion */

		///
		/// @brief 打开指示灯。
		///
		///
		void TurnOn()
		{
			if (_state == base::led::State::On)
			{
				return;
			}

			_state = base::led::State::On;
			update();
		}

		///
		/// @brief 关闭指示灯。
		///
		///
		void TurnOff()
		{
			if (_state == base::led::State::Off)
			{
				return;
			}

			_state = base::led::State::Off;
			update();
		}

		///
		/// @brief 翻转指示灯。
		///
		///
		void Toggle()
		{
			if (_state == base::led::State::On)
			{
				TurnOff();
			}
			else
			{
				TurnOn();
			}
		}

		///
		/// @brief LED 灯的状态。
		///
		/// @return
		///
		base::led::State State() const
		{
			return _state;
		}

		///
		/// @brief 设置 LED 灯的状态。
		///
		/// @param value
		///
		void SetState(base::led::State value)
		{
			if (value == base::led::State::On)
			{
				TurnOn();
			}
			else
			{
				TurnOff();
			}
		}

		///
		/// @brief 指示灯打开时的颜色。
		///
		/// @return
		///
		QColor OnColor() const
		{
			return _on_color;
		}

		///
		/// @brief 设置指示灯打开时的颜色。
		///
		/// @param value
		///
		void SetOnColor(QColor value)
		{
			if (_on_color == value)
			{
				return;
			}

			_on_color = value;

			// 触发重绘
			update();
		}

		///
		/// @brief 指示灯关闭时的颜色。
		///
		/// @return
		///
		QColor OffColor() const
		{
			return _off_color;
		}

		///
		/// @brief 设置指示灯关闭时的颜色。
		///
		/// @param value
		///
		void SetOffColor(QColor value)
		{
			if (_off_color == value)
			{
				return;
			}

			_off_color = value;

			// 触发重绘
			update();
		}

		///
		/// @brief 指示灯当前的颜色。
		///
		/// @return
		///
		QColor CurrentColor() const
		{
			if (_state == base::led::State::Off)
			{
				return _off_color;
			}

			return _on_color;
		}
	};

} // namespace widget
