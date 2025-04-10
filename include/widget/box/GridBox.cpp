#include "GridBox.h"
#include "base/string/define.h"
#include "GridBoxItem.h"
#include <cstdint>
#include <stdexcept>

/* #region 构造函数 */

widget::GridBox::GridBox()
{
	_grid_layout.setSpacing(10);
	SetPadding(widget::Padding{0});
}

widget::GridBox::GridBox(std::initializer_list<widget::GridBoxItem> const &items)
	: GridBox()
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

widget::GridBox::GridBox(std::initializer_list<widget::LabelValueUnitGridItem> const &items)
{
	try
	{
		for (widget::LabelValueUnitGridItem const &item : items)
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

/* #endregion */

void widget::GridBox::AddItem(widget::GridBoxItem const &item)
{
	for (auto &item_list_item : _item_list)
	{
		if (item_list_item.Widget() == item.Widget())
		{
			throw std::invalid_argument{CODE_POS_STR + "不能重复添加同一个对象。"};
		}
	}

	_grid_layout.addWidget(item.Widget().get(),
						   item.Row(),
						   item.Column(),
						   item.RowSpan(),
						   item.ColumnSpan(),
						   item.Align());

	_item_list.Add(item);
}

void widget::GridBox::AddItem(widget::LabelValueUnitGridItem const &item)
{
	widget::GridBoxItem label{
		item.Row(),
		item.Column() * 3,
		Qt::AlignmentFlag::AlignLeft,
		item.Lable(),
	};

	widget::GridBoxItem data{
		item.Row(),
		item.Column() * 3 + 1,
		Qt::AlignmentFlag::AlignLeft,
		item.Data(),
	};

	widget::GridBoxItem unit{
		item.Row(),
		item.Column() * 3 + 2,
		Qt::AlignmentFlag::AlignLeft,
		item.Unit(),
	};

	AddItem(label);
	AddItem(data);
	AddItem(unit);
}

void widget::GridBox::SetItem(widget::GridBoxItem const &item)
{
	RemoveWidget(item.Row(), item.Column());

	_grid_layout.addWidget(item.Widget().get(),
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
			_grid_layout.removeWidget(_item_list[i].Widget().get());
			_item_list.RemoveAt(i);

			// 移除后不返回。因为可能有多个控件同时层叠放置在同一个格子。
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
			_grid_layout.removeWidget(widget.get());
			_item_list.RemoveAt(i);
			return;
		}
	}
}

void widget::GridBox::ClearWidgets()
{
	for (auto &item : _item_list)
	{
		_grid_layout.removeWidget(item.Widget().get());
	}

	_item_list.Clear();
}

/* #endregion */

/* #region 缩放因子 */

int widget::GridBox::RowStretch(int row) const
{
	return _grid_layout.rowStretch(row);
}

void widget::GridBox::SetRowStretch(int row, int stretch)
{
	_grid_layout.setRowStretch(row, stretch);
}

void widget::GridBox::SetRowStretch(std::vector<int> const &stretch_vec)
{
	for (uint32_t i = 0; i < stretch_vec.size(); i++)
	{
		SetRowStretch(i, stretch_vec[i]);
	}
}

int widget::GridBox::ColumnStretch(int column) const
{
	return _grid_layout.columnStretch(column);
}

void widget::GridBox::SetColumnStretch(int column, int stretch)
{
	_grid_layout.setColumnStretch(column, stretch);
}

void widget::GridBox::SetColumnStretch(std::vector<int> const &stretch_vec)
{
	for (uint32_t i = 0; i < stretch_vec.size(); i++)
	{
		SetColumnStretch(i, stretch_vec[i]);
	}
}

/* #endregion */

/* #region 网格盒子的样式 */

Qt::AlignmentFlag widget::GridBox::Alignment() const
{
	return static_cast<Qt::AlignmentFlag>(_grid_layout.alignment().toInt());
}

void widget::GridBox::SetAlignment(Qt::AlignmentFlag alignment)
{
	_grid_layout.setAlignment(alignment);
}

widget::Padding widget::GridBox::Padding() const
{
	QMargins qmargin = _grid_layout.contentsMargins();

	return widget::Padding{
		qmargin.left(),
		qmargin.top(),
		qmargin.right(),
		qmargin.bottom(),
	};
}

void widget::GridBox::SetPadding(widget::Padding const &value)
{
	_grid_layout.setContentsMargins(value.Left(), value.Top(),
									value.Right(), value.Bottom());
}

/* #endregion */
