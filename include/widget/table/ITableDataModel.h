#pragma once
#include "base/delegate/IEvent.h"
#include "base/math/PositionRange.h"
#include "QString"
#include "VerticalScrollEventArgs.h"
#include "widget/table/CurrentChangeEventArgs.h"
#include "widget/table/RowInsertedEventArgs.h"
#include "widget/table/RowRemovedEventArgs.h"
#include <cstdint>

namespace widget
{
	class Table;

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
		virtual ~ITableDataModel() = default;

		///
		/// @brief 父表格。
		///
		/// @note 当表格数据模型被设置为一个表格的模型时，表格对象内部会调用 SetParentTable
		/// 把自己的指针传进来。
		///
		/// @return
		///
		virtual widget::Table *ParentTable() = 0;

		///
		/// @brief 设置父表格。
		///
		/// @note 当表格数据模型被设置为一个表格的模型时，表格对象内部会调用 SetParentTable
		/// 把自己的指针传进来。
		///
		/// @param table
		///
		virtual void SetParentTable(widget::Table *table) = 0;

		///
		/// @brief 行数。
		///
		/// @return
		///
		virtual int RowCount() const = 0;

		///
		/// @brief 列数。
		///
		/// @return
		///
		virtual int ColumnCount() const = 0;

		///
		/// @brief 是否有行标题。
		///
		/// @note 默认实现为没有。
		///
		/// @return
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
		/// @return
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
		///
		/// @return
		///
		virtual QString RowTitle(int row) const
		{
			std::string str = std::to_string(row);
			return QString{str.c_str()};
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
		virtual QString ColumnTitle(int column) const
		{
			std::string str = std::to_string(column);
			return QString{str.c_str()};
		}

		///
		/// @brief 数据。
		///
		/// @param row 数据单元格所在的行。
		/// @param column 数据单元格所在的列。
		///
		/// @return
		///
		virtual QString Data(int row, int column) const = 0;

		///
		/// @brief 对数据进行排序。
		///
		/// @param column 作为排序依据的列。
		/// @param ascending 为 true 表示升序排列，即从小到大排列。
		///
		virtual void Sort(int column, bool ascending) = 0;

		/* #region 处理表格事件 */

		///
		/// @brief 垂直滚动事件处理函数。
		///
		/// @param args
		///
		virtual void OnVerticalScroll(widget::VerticalScrollEventArgs const &args) = 0;

		///
		/// @brief 处理当前焦点单元格发生改变。
		///
		/// @return
		///
		virtual void OnCurrentChange(widget::CurrentChangeEventArgs const &args) = 0;

		/* #endregion */

		/* #region 对外提供事件 */

		///
		/// @brief 需要重置整个模型时触发。
		///
		/// @return
		///
		virtual base::IEvent<> &ModelRestEvent() = 0;

		///
		/// @brief 行被插入事件。
		///
		/// @return
		///
		virtual base::IEvent<widget::RowInsertedEventArgs const &> &RowInsertedEvent() = 0;

		///
		/// @brief 行被移除事件。
		///
		/// @return
		///
		virtual base::IEvent<widget::RowRemovedEventArgs const &> &RowRemovedEvent() = 0;

		///
		/// @brief 数据发生更改。
		///
		/// @return 事件参数指示了发生更改的数据的范围。
		///
		virtual base::IEvent<base::PositionRange<int32_t> const &> &DataChangeEvent() = 0;

		/* #endregion */

	}; // ITableDataModel

} // namespace widget
