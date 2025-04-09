#include "GridBox.h"
#include "base/string/define.h"
#include <stdexcept>

widget::GridBox::GridBox(std::initializer_list<widget::GridBoxItem> items)
{
	try
	{
		for (widget::GridBoxItem const &item : items)
		{
			AddItem(item);
		}
	}
	catch (std::exception const &e)
	{
		throw std::runtime_error{CODE_POS_STR + e.what()};
	}
	catch (...)
	{
		throw std::runtime_error{CODE_POS_STR + "未知的异常。"};
	}
}

void widget::GridBox::AddItem(widget::GridBoxItem const &item)
{
	_grid_layout->addWidget(item.Widget().get(),
							item.Row(),
							item.Column(),
							item.RowSpan(),
							item.ColumnSpan(),
							item.Align());

	_item_list.Add(item);
}

/* #region 移除控件 */

void widget::GridBox::RemoveWidget(int row, int column)
{
	for (int i = _item_list.Count() - 1; i >= 0; i--)
	{
		if (_item_list[i].Row() == row && _item_list[i].Column() == column)
		{
			_grid_layout->removeWidget(_item_list[i].Widget().get());
			_item_list.RemoveAt(i);
			return;
		}
	}
}

void widget::GridBox::RemoveWidget(std::shared_ptr<QWidget> widget)
{
	if (widget == nullptr)
	{
		return;
	}

	for (int i = _item_list.Count() - 1; i >= 0; i--)
	{
		if (_item_list[i].Widget() == widget)
		{
			_grid_layout->removeWidget(widget.get());
			_item_list.RemoveAt(i);
			return;
		}
	}
}

void widget::GridBox::ClearWidgets()
{
	for (auto &item : _item_list)
	{
		_grid_layout->removeWidget(item.Widget().get());
	}

	_item_list.Clear();
}

/* #endregion */

/* #region 缩放因子 */

int widget::GridBox::RowStretch(int row) const
{
	return _grid_layout->rowStretch(row);
}

void widget::GridBox::SetRowStretch(int row, int stretch)
{
	_grid_layout->setRowStretch(row, stretch);
}

int widget::GridBox::ColumnStretch(int column) const
{
	return _grid_layout->columnStretch(column);
}

void widget::GridBox::SetColumnStretch(int column, int stretch)
{
	_grid_layout->setColumnStretch(column, stretch);
}

/* #endregion */

/* #region 网格盒子的样式 */

Qt::AlignmentFlag widget::GridBox::Alignment() const
{
	return static_cast<Qt::AlignmentFlag>(_grid_layout->alignment().toInt());
}

void widget::GridBox::SetAlignment(Qt::AlignmentFlag alignment)
{
	_grid_layout->setAlignment(alignment);
}

widget::Padding widget::GridBox::Padding() const
{
	QMargins qmargin = _grid_layout->contentsMargins();

	return widget::Padding{
		qmargin.left(),
		qmargin.top(),
		qmargin.right(),
		qmargin.bottom(),
	};
}

void widget::GridBox::SetPadding(widget::Padding const &value)
{
	_grid_layout->setContentsMargins(value.Left(), value.Top(),
									 value.Right(), value.Bottom());
}

/* #endregion */
