#pragma once
#include "qtableview.h"

namespace widget
{
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
		QTableView *_table_view = nullptr;
		widget::VerticalScrollDirection _direction;

	public:
		constexpr VerticalScrollEventArgs(QTableView *table_view,
										  widget::VerticalScrollDirection direction)
		{
			_table_view = table_view;
			_direction = direction;
		}

		constexpr QTableView *TableView() const
		{
			return _table_view;
		}

		///
		/// @brief 当前第一个可见行的行索引。
		///
		/// @note 如果表格内没有行，将会返回 -1.
		///
		/// @return
		///
		constexpr int FirstVisibleRowIndex() const
		{
			return _table_view->rowAt(0);
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
