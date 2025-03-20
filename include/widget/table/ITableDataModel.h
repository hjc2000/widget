#pragma once
#include "QString"

namespace widget
{
	///
	/// @brief 表格数据模型。
	///
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
	};
} // namespace widget
