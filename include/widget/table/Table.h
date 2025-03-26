#pragma once
#include "base/IIdToken.h"
#include "QHeaderView"
#include "QTableView"
#include "widget/layout/HBoxLayout.h"
#include "widget/table/ITableDataModel.h"
#include "widget/table/TableSortingParameter.h"

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

		base::SpIIdToken _model_reset_event_token;
		base::SpIIdToken _row_inserted_event_token;
		base::SpIIdToken _row_removed_event_token;
		base::SpIIdToken _data_change_event_token;

		void SubscribeEvent();
		void UnsubscribeEvent();

	public:
		Table();

		///
		/// @brief 设置数据模型。
		///
		/// @note 设置模型后会自动调用 DataModelHasChanged，不需要手动调用。
		///
		/// @param model
		///
		void SetModel(std::shared_ptr<widget::ITableDataModel> const &model);

		/* #region 排序 */

		///
		/// @brief 排序是否使能。
		///
		/// @return true
		/// @return false
		///
		bool IsSortingEnabled() const;

		///
		/// @brief 使能排序。
		///
		/// @param enable 传入 true 表示使能，传入 false 表示失能。
		///
		void EnableSorting(bool enable);

		///
		/// @brief 获取表格当前的排序参数。
		///
		/// @note 如果表格没有被排序过，即用户没有点击表头进行排序，并且本类的 Sort 方法没被调用过，
		/// 本方法返回的是默认的 widget::TableSortingParameter.
		///
		/// @note 如果没有设置过数据模型，本方法返回的是默认的 widget::TableSortingParameter.
		///
		/// @return widget::TableSortingParameter
		///
		widget::TableSortingParameter CurrentSortingParameter() const;

		///
		/// @brief 排序。
		///
		/// @note 在设置数据模型之前，本方法没有任何作用。
		///
		/// @param parameter
		///
		void Sort(widget::TableSortingParameter const &parameter);

		///
		/// @brief 排序。
		///
		/// @note 在设置数据模型之前，本方法没有任何作用。
		///
		/// @param column
		/// @param order
		///
		void Sort(int column, Qt::SortOrder order);

		/* #endregion */

		///
		/// @brief 设置每一列的大小调整方式。
		///
		/// @param resize_modes
		///
		void SetResizeModes(std::vector<QHeaderView::ResizeMode> resize_modes);
	};
} // namespace widget
