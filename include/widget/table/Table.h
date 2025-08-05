#pragma once
#include "base/delegate/IEvent.h"
#include "base/math/ColumnIndex.h"
#include "base/math/Position.h"
#include "QHeaderView"
#include "qscrollbar.h"
#include "QTableView"
#include "widget/layout/VBoxLayout.h"
#include "widget/table/ITableDataModel.h"
#include "widget/table/TableSortingParameter.h"
#include <vector>

namespace widget
{
	///
	/// @brief 表格。
	///
	/// @note 表格默认会撑开，占满父容器，如果父容器可以被撑开，则会将父容器也撑开。
	///
	class Table :
		public QWidget
	{
	private:
		class PrivateTable;
		class CustomItemDelegate;
		class TableDataModelWrapper;
		class HeaderView;

	public:
		/* #region CurrentChangeEventArgs */

		class CurrentChangeEventArgs
		{
		private:
			QModelIndex _current;
			QModelIndex _previous;

		public:
			CurrentChangeEventArgs(QModelIndex const &current,
								   QModelIndex const &previous)
			{
				_current = current;
				_previous = previous;
			}

			QModelIndex Current() const
			{
				return _current;
			}

			QModelIndex Previous() const
			{
				return _previous;
			}
		};

		/* #endregion */

	private:
		std::shared_ptr<PrivateTable> _table;
		std::shared_ptr<TableDataModelWrapper> _table_data_model;
		std::shared_ptr<HeaderView> _row_header_view;
		std::shared_ptr<HeaderView> _column_header_view;
		widget::VBoxLayout _layout{this};

		void SetColumnHeaderStyle();

		void SubscribeEvents();

	public:
		Table();

		~Table();

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

		/* #region 列宽 */

		///
		/// @brief 设置每一列的大小调整方式。
		///
		/// @param resize_modes
		///
		void SetColumnResizeModes(std::vector<QHeaderView::ResizeMode> resize_modes);

		///
		/// @brief 调整所有列的宽度为适应内容。
		///
		///
		void ResizeColumnsToContents();

		///
		/// @brief 获取指定列的宽度。
		///
		/// @param column_index
		/// @return int
		///
		int ColumnWidth(int column_index) const;

		///
		/// @brief 设置指定列的宽。
		///
		/// @param index
		/// @param width
		///
		void SetColumnWidth(base::ColumnIndex const &index, int width);

		///
		/// @brief 设置所有列的宽为相同的值。
		///
		/// @param width
		///
		void SetColumnWidth(int width);

		///
		/// @brief 设置列宽。向量中每一个值都对应一个列。
		///
		/// @param widths
		///
		void SetColumnWidth(std::vector<int> const &widths);

		/* #endregion */

		///
		/// @brief 单元格的边距。
		///
		/// @return
		///
		widget::Padding ItemPadding() const;

		///
		/// @brief 设置单元格的边距。
		///
		/// @param value
		///
		void SetItemPadding(widget::Padding const &value);

		///
		/// @brief 行标题单元格的内边距。
		///
		/// @return
		///
		widget::Padding RowHeaderPadding() const;

		///
		/// @brief 设置行标题单元格的内边距。
		///
		/// @param value
		///
		void SetRowHeaderPadding(widget::Padding const &value);

		///
		/// @brief 行标题单元格的文本对齐方式。
		///
		/// @return
		///
		Qt::AlignmentFlag RowHeaderTextAlignment() const;

		///
		/// @brief 设置行标题单元格的文本对齐方式。
		///
		/// @param value
		///
		void SetRowHeaderTextAlignment(Qt::AlignmentFlag value);

		///
		/// @brief 设置内容的各个列的对齐方式。不包括表头。
		///
		/// @param alignments
		///
		void SetItemColumnAlignments(std::vector<Qt::AlignmentFlag> const &alignments);

		///
		/// @brief 第一个可见行的行索引。
		///
		/// @return
		///
		int FirstVisibleRowIndex() const;

		/* #region 事件 */

		///
		/// @brief 单元格被双击事件。
		///
		/// @return base::IEvent<base::Position const &>&
		///
		base::IEvent<base::Position<int32_t> const &> &DoubleClickEvent();

		///
		/// @brief 当前焦点单元格发生改变的事件。
		///
		/// @return
		///
		base::IEvent<widget::Table::CurrentChangeEventArgs const &> &CurrentChangeEvent();

		///
		/// @brief 垂直滚动事件。
		///
		/// @note 只要尝试滚动就会触发此事件。
		///
		/// @note 滚动条没有到顶或到底时，滚动会触发此事件，传入当前滚动到的位置。
		///
		/// @note 滚动条已经到顶或到底了，继续尝试滚动，滚不动了，当前位置不会改变，但是仍然会
		/// 触发此事件，只不过传入的位置信息一直是不变的，一直是顶部或底部位置。
		///
		/// @return
		///
		base::IEvent<QScrollBar &> &VerticalScrollEvent();

		/* #endregion */
	};

} // namespace widget
