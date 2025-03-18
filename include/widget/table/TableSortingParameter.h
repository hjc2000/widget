#pragma once
#include <qnamespace.h>

namespace widget
{
	///
	/// @brief 表格的排序方法中传递的参数。
	///
	///
	class TableSortingParameter
	{
	private:
		int _column = -1;
		Qt::SortOrder _order{};

	public:
		TableSortingParameter() = default;

		TableSortingParameter(int column, Qt::SortOrder order);

		///
		/// @brief 排序的列。
		///
		/// @return int 返回负数表示没有列被排序，所有列都处于未排序状态。返回 >=0 的数
		/// 表示被排序的列的索引。
		///
		int Column() const
		{
			return _column;
		}

		///
		/// @brief 被排序的列（如果有的话）的数据排列顺序。
		///
		/// @return Qt::SortOrder
		///
		Qt::SortOrder Order() const
		{
			return _order;
		}
	};
} // namespace widget
