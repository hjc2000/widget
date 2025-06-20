#pragma once
#include "base/delegate/IEvent.h"
#include "base/math/PositionRange.h"
#include "base/math/RowCount.h"
#include "base/math/RowIndex.h"
#include "QString"
#include <cstdint>

namespace widget
{
	///
	/// @brief 表格数据模型。
	///
	/// @note qt 的表格支持虚拟化，仅会从表格数据模型中获取当前窗口中看得到的行和列。
	/// 所以在实现表格数据模型时，只需要处理好 Data 回调就行，被回调索要哪一个行列的
	/// 数据，就获取那个数据。
	///
	/// @note 此外，用户可以在 Data 回调中自己设计缓存机制，避免滚动较快时过快地从数据源
	/// 获取数据。
	///
	class ITableDataModel
	{
	public:
		///
		/// @brief 行数。
		///
		/// @return int
		///
		virtual int RowCount() const = 0;

		///
		/// @brief 列数。
		///
		/// @return int
		///
		virtual int ColumnCount() const = 0;

		///
		/// @brief 是否有行标题。
		///
		/// @note 默认实现为没有。
		///
		/// @return true 有行标题。
		/// @return false 无行标题。
		///
		virtual bool HasRowTitle() const
		{
			return false;
		}

		///
		/// @brief 是否有列标题。
		///
		/// @note 默认实现为有。
		///
		/// @return true 有列标题。
		/// @return false 无列标题。
		///
		virtual bool HasColumnTitle() const
		{
			return true;
		}

		///
		/// @brief 行标题。
		///
		/// @note 行标题位于每一行的最左侧。
		/// @note 默认实现返回行号字符串。
		///
		/// @param row
		/// @return QString
		///
		virtual QString RowTitle(int row) const;

		///
		/// @brief 列标题。
		///
		/// @note 列标题位于每一列的最上方。
		/// @note 默认实现返回列号字符串。
		///
		/// @param column
		/// @return QString
		///
		virtual QString ColumnTitle(int column) const;

		///
		/// @brief 数据。
		///
		/// @param row 数据单元格所在的行。
		/// @param column 数据单元格所在的列。
		/// @return QString
		///
		virtual QString Data(int row, int column) const = 0;

		///
		/// @brief 对数据进行排序。
		///
		/// @param column 作为排序依据的列。
		/// @param ascending 为 true 表示升序排列，即从小到大排列。
		///
		virtual void Sort(int column, bool ascending) = 0;

		/* #region 事件 */

		///
		/// @brief 需要重置整个模型时触发。
		///
		/// @return base::IEvent<>&
		///
		virtual base::IEvent<> &ModelRestEvent() = 0;

		///
		/// @brief 行被插入事件。
		///
		/// @return base::IEvent<base::RowIndex const &, base::RowCount const &>&
		///
		/// 	@note 其中 RowIndex 指的是新行插入后，新行所在的起始索引在哪。
		/// 	例如在末尾插入，当前有 2 行，最后一行的索引是 1, 新插入 2 行到末尾，
		/// 	则 RowIndex = 2, RowCount = 2.
		///
		virtual base::IEvent<base::RowIndex const &, base::RowCount const &> &RowInsertedEvent() = 0;

		///
		/// @brief 行被移除事件。
		///
		/// @return base::IEvent<base::RowIndex const &, base::RowCount const &>&
		///
		virtual base::IEvent<base::RowIndex const &, base::RowCount const &> &RowRemovedEvent() = 0;

		///
		/// @brief 数据发生更改。
		///
		/// @return base::IEvent<base::PositionRange const &>& 事件参数指示了发生更改的数据的范围。
		///
		virtual base::IEvent<base::PositionRange<int32_t> const &> &DataChangeEvent() = 0;

		/* #endregion */
	};
} // namespace widget
