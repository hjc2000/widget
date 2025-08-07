#pragma once

namespace widget
{
	class Table;

	enum class VerticalScrollDirection
	{
		Up,
		Down
	};

	///
	/// @brief 垂直滚动事件参数。
	///
	///
	class VerticalScrollEventArgs
	{
	private:
		widget::VerticalScrollDirection _direction;

	public:
		VerticalScrollEventArgs(widget::VerticalScrollDirection direction)
		{
			_direction = direction;
		}

		///
		/// @brief 滚动方向。
		///
		/// @return
		///
		widget::VerticalScrollDirection Direction() const
		{
			return _direction;
		}
	};

} // namespace widget
