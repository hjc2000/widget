#include "GridBox.h"
#include "base/string/define.h"
#include "GridBoxItem.h"
#include <algorithm>
#include <cstdint>
#include <stdexcept>

/* #region 构造函数 */

widget::GridBox::GridBox(std::initializer_list<widget::LabelValueUnitGridItem> const &items)
{
	try
	{
		int max_column = 0;

		for (widget::LabelValueUnitGridItem const &item : items)
		{
			max_column = std::max(max_column, item.Column());

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

		for (int i = 0; i <= max_column; i++)
		{
			SetColumnStretch(i * 3 + 0, 0);
			SetColumnStretch(i * 3 + 1, 1);
			SetColumnStretch(i * 3 + 2, 0);
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
