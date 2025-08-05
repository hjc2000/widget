#pragma once
#include "qscrollbar.h"

namespace widget
{
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

		constexpr QScrollBar *ScrollBar() const
		{
			return _scroll_bar;
		}

		constexpr int FirstVisibleRowIndex() const
		{
			return _first_visible_row;
		}
	};

} // namespace widget
