#pragma once
#include "qobject.h"

namespace widget
{
	/**
	 * @brief 表格数据模型。
	 *
	 */
	class ITableDataModel
	{
	public:
		/**
		 * @brief 行数。
		 *
		 * @return int
		 */
		virtual int RowCount() const = 0;

		/**
		 * @brief 列数。
		 *
		 * @return int
		 */
		virtual int ColumnCount() const = 0;

		/**
		 * @brief 是否有行标题。
		 *
		 * @return true 有行标题。
		 * @return false 无行标题。
		 */
		virtual bool HasRowTitle() const = 0;

		/**
		 * @brief 是否有列标题。
		 *
		 * @return true 有列标题。
		 * @return false 无列标题。
		 */
		virtual bool HasColumnTitle() const = 0;

		/**
		 * @brief 行标题。
		 *
		 * @note 行标题位于每一行的最左侧。
		 *
		 * @param row
		 * @return QString
		 */
		virtual QString RowTitle(int row) const = 0;

		/**
		 * @brief 列标题。
		 *
		 * @note 列标题位于每一列的最上方。
		 *
		 * @param column
		 * @return QString
		 */
		virtual QString ColumnTitle(int column) const = 0;

		/**
		 * @brief 数据。
		 *
		 * @param row
		 * @param column
		 * @return QString
		 */
		virtual QString Data(int row, int column) const = 0;

	public:
		/**
		 * @brief 对数据进行排序。
		 *
		 * @param ascending 为 true 表示升序排列，即从小到大排列。
		 */
		virtual void Sort(bool ascending) = 0;
	};
} // namespace widget
