#include "GridBoxItem.h"
#include "base/string/define.h"
#include <stdexcept>

widget::GridBoxItem::GridBoxItem(int row, int column, std::shared_ptr<QWidget> widget)
{
	if (widget == nullptr)
	{
		throw std::invalid_argument{CODE_POS_STR + "禁止传入空指针。"};
	}

	_row = row;
	_column = column;
	_widget = widget;
}

widget::GridBoxItem::GridBoxItem(int row, int column,
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

widget::GridBoxItem::GridBoxItem(int row, int column,
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
