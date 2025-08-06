#pragma once
#include "base/delegate/Delegate.h"
#include "base/math/math.h"
#include "base/string/String.h"
#include "ITableDataModel.h"
#include "qobject.h"
#include "qscrollbar.h"
#include <cstdint>

namespace widget
{
	class VirtualizedTableDataModel :
		public widget::ITableDataModel
	{
	private:
		QObject _q_object;
		int64_t _start = 0;
		int64_t _end = 0;

		base::Delegate<> _model_reset_event;
		base::Delegate<widget::RowInsertedEventArgs const &> _row_inserted_event;
		base::Delegate<widget::RowRemovedEventArgs const &> _row_removed_event;
		base::Delegate<base::PositionRange<int32_t> const &> _data_change_event;

		/* #region 事件 */

		///
		/// @brief 需要重置整个模型时触发。
		///
		/// @return
		///
		virtual base::IEvent<> &ModelRestEvent() override final
		{
			return _model_reset_event;
		}

		///
		/// @brief 行被插入事件。
		///
		/// @return
		///
		virtual base::IEvent<widget::RowInsertedEventArgs const &> &RowInsertedEvent() override final
		{
			return _row_inserted_event;
		}

		///
		/// @brief 行被移除事件。
		///
		/// @return
		///
		virtual base::IEvent<widget::RowRemovedEventArgs const &> &RowRemovedEvent() override final
		{
			return _row_removed_event;
		}

		///
		/// @brief 数据发生更改。
		///
		/// @return 事件参数指示了发生更改的数据的范围。
		///
		virtual base::IEvent<base::PositionRange<int32_t> const &> &DataChangeEvent() override final
		{
			return _data_change_event;
		}

		/* #endregion */

		///
		/// @brief 行数。
		///
		/// @return
		///
		virtual int RowCount() const override final
		{
			return _end - _start;
		}

		///
		/// @brief 行标题。
		///
		/// @note 行标题位于每一行的最左侧。
		/// @note 默认实现返回行号字符串。
		///
		/// @param row
		///
		/// @return
		///
		virtual QString RowTitle(int row) const override final
		{
			return RealRowTitle(static_cast<int64_t>(row) + _start);
		}

		///
		/// @brief 数据。
		///
		/// @param row 数据单元格所在的行。
		/// @param column 数据单元格所在的列。
		///
		/// @return
		///
		virtual QString Data(int row, int column) const override final
		{
			return RealData(static_cast<int64_t>(row) + _start, column);
		}

		///
		/// @brief 垂直滚动事件处理函数。
		///
		/// @param args
		///
		virtual void OnVerticalScroll(widget::VerticalScrollEventArgs const &args) override final
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

		///
		/// @brief 移动列表窗口。
		///
		/// @param step
		/// @return
		///
		bool TryMove(int64_t step)
		{
			if (_start + step < 0)
			{
				return false;
			}

			if (_end + step > RealRowCount())
			{
				return false;
			}

			_start += step;
			_end += step;
			return true;
		}

		///
		/// @brief 尽可能移动列表窗口。如果窗口已经顶到列表边界了就会无法继续移动更多。
		///
		/// @param step
		///
		/// @return 实际移动距离。
		///
		int64_t TryMoveAsFarAsPossible(int64_t step)
		{
			int64_t delta = 0;

			if (step > 0)
			{
				int64_t avalible = RealRowCount() - _end;
				delta = std::min(step, avalible);
				TryMove(delta);
			}
			else if (step < 0)
			{
				int64_t avalible = -_start;
				delta = std::max(step, avalible);
				TryMove(delta);
			}

			return delta;
		}

	public:
		virtual ~VirtualizedTableDataModel() = default;

		virtual int64_t RealRowCount() const = 0;

		///
		/// @brief 列数。
		///
		/// @return
		///
		virtual int ColumnCount() const override = 0;

		///
		/// @brief 是否有行标题。
		///
		/// @note 默认实现为没有。
		///
		/// @return
		///
		virtual bool HasRowTitle() const override
		{
			return false;
		}

		///
		/// @brief 是否有列标题。
		///
		/// @note 默认实现为有。
		///
		/// @return
		///
		virtual bool HasColumnTitle() const override
		{
			return true;
		}

		virtual QString RealRowTitle(int64_t row) const
		{
			base::String str = std::to_string(row);
			str.PadLeft(' ', base::StringLength{19});
			return QString{str.StdString().c_str()};
		}

		///
		/// @brief 列标题。
		///
		/// @note 列标题位于每一列的最上方。
		/// @note 默认实现返回列号字符串。
		///
		/// @param column
		///
		/// @return
		///
		virtual QString ColumnTitle(int column) const override
		{
			std::string str = std::to_string(column);
			return QString{str.c_str()};
		}

		virtual QString RealData(int64_t row, int64_t column) const = 0;

		///
		/// @brief 对数据进行排序。
		///
		/// @param column 作为排序依据的列。
		/// @param ascending 为 true 表示升序排列，即从小到大排列。
		///
		virtual void Sort(int column, bool ascending) override = 0;
	};

} // namespace widget
