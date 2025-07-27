#pragma once
#include "base/string/define.h"
#include "qwidget.h"
#include <memory>
#include <stdexcept>

namespace widget
{
	class GridBoxItem final
	{
	private:
		int _row = 0;
		int _column = 0;
		int _row_span = 1;
		int _column_span = 1;

		///
		/// @brief 默认使用 static_cast<Qt::AlignmentFlag>(0), 元素会充满整个
		/// 网格的格子。
		///
		Qt::AlignmentFlag _align = static_cast<Qt::AlignmentFlag>(0);

		std::shared_ptr<QWidget> _widget;

	public:
		GridBoxItem(int row, int column, std::shared_ptr<QWidget> widget)
		{
			if (widget == nullptr)
			{
				throw std::invalid_argument{CODE_POS_STR + "禁止传入空指针。"};
			}

			_row = row;
			_column = column;
			_widget = widget;
		}

		GridBoxItem(int row, int column, Qt::AlignmentFlag align, std::shared_ptr<QWidget> widget)
		{
			if (widget == nullptr)
			{
				throw std::invalid_argument{CODE_POS_STR + "禁止传入空指针。"};
			}

			_row = row;
			_column = column;
			_align = align;
			_widget = widget;
		}

		GridBoxItem(int row, int column,
					int row_span, int column_span,
					std::shared_ptr<QWidget> widget)
		{
			if (widget == nullptr)
			{
				throw std::invalid_argument{CODE_POS_STR + "禁止传入空指针。"};
			}

			_row = row;
			_column = column;
			_row_span = row_span;
			_column_span = column_span;
			_widget = widget;
		}

		GridBoxItem(int row, int column,
					int row_span, int column_span,
					Qt::AlignmentFlag align,
					std::shared_ptr<QWidget> widget)
		{
			if (widget == nullptr)
			{
				throw std::invalid_argument{CODE_POS_STR + "禁止传入空指针。"};
			}

			_row = row;
			_column = column;
			_row_span = row_span;
			_column_span = column_span;
			_align = align;
			_widget = widget;
		}

		int Row() const
		{
			return _row;
		}

		int Column() const
		{
			return _column;
		}

		int RowSpan() const
		{
			return _row_span;
		}

		int ColumnSpan() const
		{
			return _column_span;
		}

		Qt::AlignmentFlag Align() const
		{
			return _align;
		}

		std::shared_ptr<QWidget> Widget() const
		{
			return _widget;
		}
	};

} // namespace widget
