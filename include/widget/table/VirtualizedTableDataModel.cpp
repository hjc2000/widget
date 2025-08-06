#include "VirtualizedTableDataModel.h" // IWYU pragma: keep
#include "base/math/math.h"
#include "base/math/RowCount.h"
#include "base/math/RowIndex.h"
#include "qscrollbar.h"

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
	if (RowCount() == 0)
	{
		// 视窗大小为 0, 这是第一次插入数据。
		if (count > 1000)
		{
			// 对 count 进行限幅，因为最多允许视窗大小为 1000.
			count = 1000;
		}

		// 设置 _start 和 _end, 直接将视窗定到第一次插入的数据那里。
		_start = index;
		_end = index + count;

		widget::RowInsertedEventArgs new_args{
			base::RowIndex{0},
			base::RowCount{count},
		};

		_row_inserted_event.Invoke(new_args);
		return;
	}

	// 不是第一次插入了，表格中已经有数据了。
	if (index >= _end)
	{
		// 在视窗后面插入
		if (RowCount() >= 1000)
		{
			// 在视窗后面插入，并且视窗已经足够大了，不需要扩大视窗，并且因为是在视窗后面，
			// 也不需要调整滚动条。直接返回。
			return;
		}

		// 算出当前视窗离 1000 行还差多少行，将 count 限幅为这个值。
		if (count > 1000 - RowCount())
		{
			count = 1000 - RowCount();
		}

		widget::RowInsertedEventArgs new_args{
			base::RowIndex{_end},
			base::RowCount{count},
		};

		_end += count;
		_row_inserted_event.Invoke(new_args);
		return;
	}

	if (index >= _start && index < _end)
	{
		// 在视窗中间插入
		count = std::min(count, _end - _start);

		_data_change_event.Invoke(base::PositionRange<int>{
			base::Position<int32_t>{0, static_cast<int32_t>(index - _start)},
			base::Position<int32_t>{ColumnCount() - 1, static_cast<int32_t>(count - 1)},
		});
	}

	// start < _start
	// 在视窗的前面插入。
	_start += count;
	_end += count;

	_data_change_event.Invoke(base::PositionRange<int32_t>{
		base::Position<int32_t>{0, 0},
		base::Position<int32_t>{ColumnCount() - 1, RowCount() - 1},
	});

	// 进行滚动条补偿。
	{
		if (TableView()->verticalScrollBar()->maximum() == 0)
		{
			return;
		}

		// 插入点的行的当前像素位置。
		int start_row_position = TableView()->rowViewportPosition(0);

		// 插入后获取原来的插入点处的行的现在的像素位置。
		int end_row_position = TableView()->rowViewportPosition(count);

		// 通过定时器延迟执行滚动条调整。等到表格重绘后执行滚动才能滚到正确的位置。
		QTimer::singleShot(
			0,
			&_q_object,
			[this, start_row_position, end_row_position]
			{
				int delta_position = end_row_position - start_row_position;
				int new_scroll_bar_position = TableView()->verticalScrollBar()->value() + delta_position;
				TableView()->verticalScrollBar()->setValue(new_scroll_bar_position);
			});
	}
}
