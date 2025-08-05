#pragma once
#include "qscrollbar.h"

namespace widget
{
	///
	/// @brief 垂直滚动事件参数。
	///
	///
	class VerticalScrollEventArgs
	{
	private:
		QScrollBar *_scroll_bar = nullptr;
		int _first_visible_row = 0;

	public:
		constexpr VerticalScrollEventArgs(QScrollBar *scroll_bar, int first_visible_row)
		{
			_scroll_bar = scroll_bar;
			_first_visible_row = first_visible_row;
		}

		///
		/// @brief 当前表格视图的滚动条对象。
		///
		/// @return
		///
		constexpr QScrollBar *ScrollBar() const
		{
			return _scroll_bar;
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
			return _first_visible_row;
		}
	};

} // namespace widget
