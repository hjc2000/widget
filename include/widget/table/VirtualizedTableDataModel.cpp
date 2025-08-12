#include "VirtualizedTableDataModel.h" // IWYU pragma: keep
#include "base/math/RowCount.h"
#include "base/math/RowIndex.h"
#include "base/string/define.h"
#include "qabstractitemmodel.h"
#include "qtimer.h"
#include "RowRemovedEventArgs.h"
#include "widget/table/Table.h"
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <stdexcept>

void widget::VirtualizedTableDataModel::ExpandWindow()
{
	int64_t size_to_expand = 1000 - RowCount();
	if (size_to_expand <= 0)
	{
		// 视窗足够大了，不需要扩展。
		return;
	}

	// 需要扩展视窗。
	if (RealRowCount() <= RowCount())
	{
		// 没有更多数据可以扩展视窗。
		return;
	}

	if (_end < RealRowCount())
	{
		// 尾部扩展
		int64_t inserted_row_count = RealRowCount() - _end;
		inserted_row_count = std::min(size_to_expand, inserted_row_count);

		widget::RowInsertedEventArgs new_args{
			base::RowIndex{_end},
			base::RowCount{inserted_row_count},
		};

		_end += inserted_row_count;
		_row_inserted_event.Invoke(new_args);
		size_to_expand -= inserted_row_count;
	}

	if (_start > 0)
	{
		// 头部扩展
		int64_t inserted_row_count = std::min(_start, size_to_expand);

		widget::RowInsertedEventArgs new_args{
			base::RowIndex{0},
			base::RowCount{inserted_row_count},
		};

		_start -= inserted_row_count;
		_row_inserted_event.Invoke(new_args);
		ParentTable()->ScrollByRow(inserted_row_count);
	}
}

void widget::VirtualizedTableDataModel::VirtualizedScrollByRow(int64_t row_step)
{
	int64_t actual_step = TryMoveAsFarAsPossible(row_step);

	_data_change_event.Invoke(base::PositionRange<int32_t>{
		base::Position<int32_t>{0, 0},
		base::Position<int32_t>{ColumnCount() - 1, RowCount() - 1},
	});

	QTimer::singleShot(
		0,
		&_q_object,
		[this, actual_step]() mutable
		{
			// 滚动方向（滚动条移动方向）与视窗移动方向相反。
			ParentTable()->ScrollByRow(-actual_step);

			int64_t relative_row_index = _current_row - _start;
			if (relative_row_index < 0 || relative_row_index >= RowCount())
			{
				relative_row_index = -1;
			}

			QModelIndex current_index = ParentTable()->CurrentIndex();

			if (relative_row_index == current_index.row())
			{
				return;
			}

			int scroll_bar_value = ParentTable()->VerticalScrollBar()->value();
			_scroll_because_of_set_current = true;
			_current_is_changed_by_virtualized_scroll = true;
			ParentTable()->SetCurrentIndex(relative_row_index, _current_column);
			ParentTable()->VerticalScrollBar()->setValue(scroll_bar_value);
			_scroll_because_of_set_current = false;
			_current_is_changed_by_virtualized_scroll = false;
		});
}

void widget::VirtualizedTableDataModel::OnVerticalScroll(widget::VerticalScrollEventArgs const &args)
{
	if (_scroll_because_of_set_current)
	{
		return;
	}

	if ((args.Direction() == widget::VerticalScrollDirection::Down) &&
		(ParentTable()->FirstVisibleRowIndex() > RowCount() - 100))
	{
		VirtualizedScrollByRow(200);
	}
	else if ((args.Direction() == widget::VerticalScrollDirection::Up) &&
			 (ParentTable()->FirstVisibleRowIndex() < 100))
	{
		VirtualizedScrollByRow(-200);
	}
}

/* #region 通知 */

void widget::VirtualizedTableDataModel::NotifyRowInserted(int64_t index, int64_t count)
{
	if (index < 0)
	{
		throw std::invalid_argument{CODE_POS_STR + "index 不能 < 0."};
	}

	if (count < 0)
	{
		throw std::invalid_argument{CODE_POS_STR + "count 不能 < 0."};
	}

	if (count == 0)
	{
		return;
	}

	QTimer::singleShot(
		0,
		&_q_object,
		[this, index, count]() mutable
		{
			if (index < _start)
			{
				// 在视窗的前面插入。
				_start += count;
				_end += count;
			}
			else if (index >= _end)
			{
				// 在视窗后面插入
			}
			else if (index >= _start && index < _end)
			{
				// 在视窗中间插入
				count = std::min(count, _end - index);

				_data_change_event.Invoke(base::PositionRange<int>{
					base::Position<int32_t>{0, static_cast<int32_t>(index - _start)},
					base::Position<int32_t>{ColumnCount() - 1, static_cast<int32_t>(count - 1)},
				});
			}

			ExpandWindow();
		});
}

void widget::VirtualizedTableDataModel::NotifyRowRemoved(int64_t index, int64_t count)
{
	if (RowCount() <= 0)
	{
		// 视窗中没有数据，不需要处理。
		return;
	}

	if (index < 0)
	{
		throw std::invalid_argument{CODE_POS_STR + "index 不能 < 0."};
	}

	if (count < 0)
	{
		throw std::invalid_argument{CODE_POS_STR + "count 不能 < 0."};
	}

	if (count == 0)
	{
		return;
	}

	QTimer::singleShot(
		0,
		&_q_object,
		[this, index, count]() mutable
		{
			if (index >= _end)
			{
				// 被移除的所有内容都在视窗之后。
				return;
			}

			// 视窗向上滑动，追上去。
			_start -= count;
			_end -= count;

			if (_start < 0)
			{
				// 追上去如果导致头部越界了，除了要对 _start 限幅到 0 以外，
				// _start 超出 0 的部分就是对于 qt 表格控件来说需要在头部移除的行数。
				int64_t should_removed_count = 0 - _start;
				_start = 0;

				widget::RowRemovedEventArgs args{
					base::RowIndex{0},
					base::RowCount{should_removed_count},
				};

				_row_removed_event.Invoke(args);
			}
		});
}

void widget::VirtualizedTableDataModel::NotifyDataChange(base::PositionRange<int64_t> const &range)
{
	if (RowCount() <= 0)
	{
		// 视窗中没有数据，不需要处理。
		return;
	}

	int64_t row_start = range.LeftTop().Y();
	int64_t column_start = range.LeftTop().X();
	int64_t row_end = range.RightBottom().Y();
	int64_t column_end = range.RightBottom().X();

	if (row_start >= _end)
	{
		// 变化的数据在视窗后面。
		return;
	}

	if (row_end < _start)
	{
		// 变化的数据在视窗前面。
		return;
	}

	// 视窗中含有变化的数据。
	if (row_start < _start)
	{
		row_start = _start;
	}

	if (row_end > _end - 1)
	{
		row_end = _end - 1;
	}

	// 求相对的起始行索引、相对的结束行列索引。
	// 即对于 qt 表格控件来说的起始行索引、结束行索引。
	row_start -= _start;
	row_end -= _start;

	_data_change_event.Invoke(base::PositionRange<int32_t>{
		base::Position<int32_t>{
			static_cast<int32_t>(row_start),
			static_cast<int32_t>(column_start),
		},
		base::Position<int32_t>{
			static_cast<int32_t>(row_end),
			static_cast<int32_t>(column_end),
		},
	});
}

/* #endregion */

void widget::VirtualizedTableDataModel::OnCurrentChange(widget::CurrentChangeEventArgs const &args)
{
	if (_current_is_changed_by_virtualized_scroll)
	{
		std::cout << "判定当前索引的改变是由虚拟化滚动引发的，忽略。真实行号：" << (args.Current().row() + _start)
				  << ", "
				  << "虚拟行号：" << args.Current().row()
				  << std::endl;

		return;
	}

	std::cout << "设置当前行。真实行号:" << (args.Current().row() + _start)
			  << ", "
			  << "虚拟行号：" << args.Current().row()
			  << std::endl;

	if (args.Current().row() < 0 || args.Current().row() >= RowCount())
	{
		_current_row = -1;
	}
	else
	{
		_current_row = args.Current().row() + _start;
	}

	if (args.Current().column() < 0 || args.Current().column() >= ColumnCount())
	{
		_current_column = -1;
	}
	else
	{
		_current_column = args.Current().column();
	}

	if (_current_row == _previous_row &&
		_current_column == _previous_column)
	{
		return;
	}

	try
	{
		OnRealCurrentChange(_current_row,
							_current_column,
							_previous_row,
							_previous_column);
	}
	catch (std::exception const &e)
	{
		std::cerr << CODE_POS_STR << e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << CODE_POS_STR << "未知异常。" << std::endl;
	}

	_previous_row = _current_row;
	_previous_column = _current_column;
}

void widget::VirtualizedTableDataModel::OnClick(base::Position<int32_t> const &position)
{
}

int64_t widget::VirtualizedTableDataModel::FirstVisibleRowIndex() const
{
	return ParentTable()->FirstVisibleRowIndex() + _start;
}

void widget::VirtualizedTableDataModel::ScrollByRow(int64_t row_step)
{
	TryMoveAsFarAsPossible(row_step);

	_data_change_event.Invoke(base::PositionRange<int32_t>{
		base::Position<int32_t>{0, 0},
		base::Position<int32_t>{ColumnCount() - 1, RowCount() - 1},
	});
}

void widget::VirtualizedTableDataModel::ScrollToRow(int64_t row_index)
{
	int64_t step = row_index - _start;
	ScrollByRow(step);
	ParentTable()->VerticalScrollBar()->setValue(1);
	ParentTable()->VerticalScrollBar()->setValue(0);
}
