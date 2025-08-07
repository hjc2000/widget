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
		widget::Table *_table = nullptr;
		widget::VerticalScrollDirection _direction;

	public:
		VerticalScrollEventArgs(widget::Table *table,
								widget::VerticalScrollDirection direction)
		{
			_table = table;
			_direction = direction;
		}

		widget::Table *Table() const
		{
			return _table;
		}

		///
		/// @brief 当前第一个可见行的行索引。
		///
		/// @note 如果表格内没有行，将会返回 -1.
		///
		/// @return
		///
		int FirstVisibleRowIndex() const;

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
