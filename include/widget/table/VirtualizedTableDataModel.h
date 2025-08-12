#pragma once
#include "base/delegate/Delegate.h"
#include "base/math/Position.h"
#include "base/string/String.h"
#include "ITableDataModel.h"
#include "qobject.h"
#include <algorithm>
#include <cstdint>
#include <iostream>

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

		bool _scroll_because_of_set_current = false;
		bool _current_is_changed_by_virtualized_scroll = false;
		int64_t _current_row = -1;
		int64_t _current_column = -1;
		int64_t _previous_row = -1;
		int64_t _previous_column = -1;

		void ExpandWindow();

		///
		/// @brief 基于行数增量进行滚动。
		///
		/// @param row_step
		///
		void VirtualizedScrollByRow(int64_t row_step);

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

		/* #region 处理表格事件 */

		///
		/// @brief 垂直滚动事件处理函数。
		///
		/// @param args
		///
		virtual void OnVerticalScroll(widget::VerticalScrollEventArgs const &args) override final;

		///
		/// @brief 处理当前焦点单元格发生改变。
		///
		/// @return
		///
		virtual void OnCurrentChange(widget::CurrentChangeEventArgs const &args) override final;

		///
		/// @brief 单击事件处理函数。
		///
		/// @param position
		///
		virtual void OnClick(base::Position<int32_t> const &position) override final;

		///
		/// @brief 双击事件处理函数。
		///
		/// @param position
		///
		virtual void OnDoubleClick(base::Position<int32_t> const &position) override final
		{
			OnRealDoubleClick(position.Y() + _start, position.X());
		}

		/* #endregion */

		/* #region 滑动窗口 */

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

		/* #endregion */

	protected:
		/* #region 通知 */

		///
		/// @brief 通知行插入。
		///
		/// @param index
		/// @param count
		///
		void NotifyRowInserted(int64_t index, int64_t count);

		///
		/// @brief 通知行移除。
		///
		/// @param index
		/// @param count
		///
		void NotifyRowRemoved(int64_t index, int64_t count);

		///
		/// @brief 通知数据发生改变。
		///
		/// @param range
		///
		void NotifyDataChange(base::PositionRange<int64_t> const &range);

		///
		/// @brief 通知数据模型重置。
		///
		///
		void NotifyModelReset()
		{
			_start = 0;
			_end = 0;
			_model_reset_event.Invoke();
		}

		/* #endregion */

	public:
		virtual ~VirtualizedTableDataModel()
		{
			std::cout << __func__ << std::endl;
		}

		///
		/// @brief 父表格。
		///
		/// @note 当表格数据模型被设置为一个表格的模型时，表格对象内部会调用 SetParentTable
		/// 把自己的指针传进来。
		///
		/// @return
		///
		virtual widget::Table *ParentTable() const override = 0;

		///
		/// @brief 设置父表格。
		///
		/// @note 当表格数据模型被设置为一个表格的模型时，表格对象内部会调用 SetParentTable
		/// 把自己的指针传进来。
		///
		/// @param table
		///
		virtual void SetParentTable(widget::Table *table) override = 0;

		///
		/// @brief 数据源中真实的行数。
		///
		/// @return
		///
		virtual int64_t RealRowCount() const = 0;

		///
		/// @brief 列数。
		///
		/// @note 列没有被虚拟化，没有真实的行数和虚拟化的行数之分。
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

		///
		/// @brief 真实数据源中的行标题。
		///
		/// @param row 对应真实数据源中的行索引。
		///
		/// @return
		///
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

		///
		/// @brief 真实的数据源中的数据。
		///
		/// @param row 真实数据源的行号。
		/// @param column 真实数据源的列号。
		///
		/// @return
		///
		virtual QString RealData(int64_t row, int64_t column) const = 0;

		///
		/// @brief 对数据进行排序。
		///
		/// @param column 作为排序依据的列。
		/// @param ascending 为 true 表示升序排列，即从小到大排列。
		///
		virtual void Sort(int column, bool ascending) override = 0;

		/* #region 事件处理函数 */

		///
		/// @brief 真实的，非虚拟化的当前选中项发生改变的事件处理函数。
		///
		/// @param current_row 当前选中的真实数据源的行号。
		/// @param current_column 当前选中的真实数据源的列号。
		/// @param previous_row 上一次选中的真实数据源的行号。
		/// @param previous_column 桑一次选中的真实数据源的列号。
		///
		virtual void OnRealCurrentChange(int64_t current_row,
										 int64_t current_column,
										 int64_t previous_row,
										 int64_t previous_column) = 0;

		///
		/// @brief 真实的单元格，非虚拟的双击事件。
		///
		/// @param row 真实的数据源的行号。
		/// @param column 真实的数据源的列号。
		///
		virtual void OnRealDoubleClick(int64_t row, int64_t column) = 0;

		/* #endregion */

		///
		/// @brief 第一个可见行的行索引。
		///
		/// @return
		///
		int64_t FirstVisibleRowIndex() const;

		///
		/// @brief 滚动指定的行数增量。
		///
		/// @param row_step
		///
		void ScrollByRow(int64_t row_step);

		///
		/// @brief 滚动到指定的行。
		///
		/// @param row_index
		///
		void ScrollToRow(int64_t row_index);

	}; // VirtualizedTableDataModel

} // namespace widget
