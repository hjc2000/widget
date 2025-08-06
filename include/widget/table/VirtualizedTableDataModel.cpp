#include "VirtualizedTableDataModel.h" // IWYU pragma: keep
#include "base/math/math.h"
#include "base/math/RowCount.h"
#include "base/math/RowIndex.h"
#include "base/string/define.h"
#include "qscrollbar.h"
#include <algorithm>
#include <cstdint>
#include <stdexcept>

void widget::VirtualizedTableDataModel::OnVerticalScroll(widget::VerticalScrollEventArgs const &args)
{
	if ((args.Direction() == widget::VerticalScrollDirection::Down) &&
		(args.FirstVisibleRowIndex() > RowCount() - 100))
	{
		QTableView *table_view = args.TableView();

		int64_t step = TryMoveAsFarAsPossible(200);

		_data_change_event.Invoke(base::PositionRange<int32_t>{
			base::Position<int32_t>{0, 0},
			base::Position<int32_t>{ColumnCount() - 1, RowCount() - 1},
		});

		{
			if (args.TableView()->verticalScrollBar()->maximum() == 0)
			{
				return;
			}

			// 插入点的行的当前像素位置。
			int start_row_position = args.TableView()->rowViewportPosition(0);

			// 插入后获取原来的插入点处的行的现在的像素位置。
			int end_row_position = args.TableView()->rowViewportPosition(step);

			// 通过定时器延迟执行滚动条调整。等到表格重绘后执行滚动才能滚到正确的位置。
			QTimer::singleShot(
				0,
				&_q_object,
				[table_view, start_row_position, end_row_position]
				{
					int delta_position = end_row_position - start_row_position;
					int new_scroll_bar_position = table_view->verticalScrollBar()->value() - delta_position;
					table_view->verticalScrollBar()->setValue(new_scroll_bar_position);
				});
		}
	}
	else if ((args.Direction() == widget::VerticalScrollDirection::Up) &&
			 (args.FirstVisibleRowIndex() < 100))
	{
		QTableView *table_view = args.TableView();

		int64_t step = TryMoveAsFarAsPossible(-200);

		_data_change_event.Invoke(base::PositionRange<int>{
			base::Position<int32_t>{0, 0},
			base::Position<int32_t>{ColumnCount() - 1, RowCount() - 1},
		});

		{
			if (args.TableView()->verticalScrollBar()->maximum() == 0)
			{
				return;
			}

			int64_t have_moved = base::abs(step);

			// 插入点的行的当前像素位置。
			int start_row_position = args.TableView()->rowViewportPosition(0);

			// 插入后获取原来的插入点处的行的现在的像素位置。
			int end_row_position = args.TableView()->rowViewportPosition(have_moved);

			// 通过定时器延迟执行滚动条调整。等到表格重绘后执行滚动才能滚到正确的位置。
			QTimer::singleShot(
				0,
				&_q_object,
				[table_view, start_row_position, end_row_position]
				{
					int delta_position = end_row_position - start_row_position;
					int new_scroll_bar_position = table_view->verticalScrollBar()->value() + delta_position;
					table_view->verticalScrollBar()->setValue(new_scroll_bar_position);
				});
		}
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
		count = std::min(count, _end - _start);

		_data_change_event.Invoke(base::PositionRange<int>{
			base::Position<int32_t>{0, static_cast<int32_t>(index - _start)},
			base::Position<int32_t>{ColumnCount() - 1, static_cast<int32_t>(count - 1)},
		});
	}

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
			int64_t delta = RealRowCount() - _end;
			delta = std::min(size_to_expand, delta);

			widget::RowInsertedEventArgs new_args{
				base::RowIndex{_end},
				base::RowCount{delta},
			};

			_end += delta;
			_row_inserted_event.Invoke(new_args);
			continue;
		}

		if (_start > 0)
		{
			int64_t delta = std::min(_start, size_to_expand);

			widget::RowInsertedEventArgs new_args{
				base::RowIndex{0},
				base::RowCount{delta},
			};

			_start -= delta;
			_row_inserted_event.Invoke(new_args);
			continue;
		}
	}
}
