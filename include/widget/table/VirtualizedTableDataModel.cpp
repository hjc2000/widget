#include "VirtualizedTableDataModel.h" // IWYU pragma: keep
#include "base/math/math.h"
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
