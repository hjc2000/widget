#pragma once
#include <QHeaderView>
#include <QTableView>
#include <widget/layout/HBoxLayout.h>
#include <widget/table/ITableDataModel.h>
#include <widget/table/TableSortingParameter.h>

namespace widget
{
	///
	/// @brief 表格。
	///
	///
	class Table :
		public QWidget
	{
	private:
		class PrivateTable;
		class CustomItemDelegate;
		class TableDataModelWrapper;

		std::shared_ptr<PrivateTable> _table;
		std::shared_ptr<TableDataModelWrapper> _table_data_model;
		widget::HBoxLayout _layout{this};

	public:
		Table();

		/* #region 数据模型 */

		///
		/// @brief 设置数据模型。
		///
		/// @param model
		///
		void SetModel(std::shared_ptr<widget::ITableDataModel> const &model);

		///
		/// @brief 设置数据模型，同时设置每一列的大小调整方式。
		///
		/// @param model
		/// @param resize_modes
		///
		void SetModel(std::shared_ptr<widget::ITableDataModel> const &model,
					  std::vector<QHeaderView::ResizeMode> resize_modes);

		///
		/// @brief 数据模型发生改变，需要刷新表格视图。
		///
		///
		void DataModelHasChanged();

		/* #endregion */

		///
		/// @brief 获取表格当前的排序参数。
		///
		/// @return widget::TableSortingParameter
		///
		widget::TableSortingParameter CurrentTableSortingParameter() const;

		///
		/// @brief 设置每一列的大小调整方式。
		///
		/// @param resize_modes
		///
		void SetResizeModes(std::vector<QHeaderView::ResizeMode> resize_modes);
	};
} // namespace widget
