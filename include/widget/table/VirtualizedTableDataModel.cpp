#include "VirtualizedTableDataModel.h" // IWYU pragma: keep
#include "base/math/RowCount.h"
#include "base/math/RowIndex.h"
#include "base/string/define.h"
#include "widget/table/Table.h"
#include <algorithm>
#include <cstdint>
#include <stdexcept>

void widget::VirtualizedTableDataModel::ExpandWindow()
{
	while (true)
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
			continue;
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
			continue;
		}
	}
}

void widget::VirtualizedTableDataModel::OnVerticalScroll(widget::VerticalScrollEventArgs const &args)
{
	if ((args.Direction() == widget::VerticalScrollDirection::Down) &&
		(ParentTable()->FirstVisibleRowIndex() > RowCount() - 100))
	{
		int64_t step = TryMoveAsFarAsPossible(200);

		_data_change_event.Invoke(base::PositionRange<int32_t>{
			base::Position<int32_t>{0, 0},
			base::Position<int32_t>{ColumnCount() - 1, RowCount() - 1},
		});

		// 滚动方向（滚动条移动方向）与视窗移动方向相反。
		ParentTable()->ScrollByRow(-step);
	}
	else if ((args.Direction() == widget::VerticalScrollDirection::Up) &&
			 (ParentTable()->FirstVisibleRowIndex() < 100))
	{
		int64_t step = TryMoveAsFarAsPossible(-200);

		_data_change_event.Invoke(base::PositionRange<int>{
			base::Position<int32_t>{0, 0},
			base::Position<int32_t>{ColumnCount() - 1, RowCount() - 1},
		});

		// 滚动方向（滚动条移动方向）与视窗移动方向相反。
		ParentTable()->ScrollByRow(-step);
	}
}

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
}

void widget::VirtualizedTableDataModel::NotifyRowRemoved(int64_t index, int64_t count)
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

	int64_t insert_end_index = index + count;

	if (insert_end_index < _start)
	{
		// 被移除的所有内容都在视窗之前。
		_start -= count;
		_end -= count;

		if (_start < 0)
		{
			_start = 0;
		}

		if (_end < 0)
		{
			_end = 0;
		}

		return;
	}

	if (index >= _end)
	{
		// 被移除的所有内容都在视窗之后。
		return;
	}

	if (index >= _start && insert_end_index <= _end)
	{
		// 被移除的所有内容都在视窗内。
	}
}
