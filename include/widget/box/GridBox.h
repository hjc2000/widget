#pragma once
#include "base/container/List.h"
#include "GridBoxItem.h"
#include "qgridlayout.h"
#include "qwidget.h"
#include "widget/layout/Padding.h"
#include <initializer_list>
#include <memory>

namespace widget
{
	class GridBox :
		public QWidget
	{
	private:
		std::shared_ptr<QGridLayout> _grid_layout{};
		base::List<widget::GridBoxItem> _item_list{};

	public:
		GridBox() = default;

		GridBox(std::initializer_list<widget::GridBoxItem> items);

		void AddItem(widget::GridBoxItem const &item);

		void RemoveWidget(std::shared_ptr<QWidget> widget);

		void ClearWidgets();

		/* #region 缩放因子 */

		///
		/// @brief 行缩放因子。
		///
		/// @param row
		/// @return int
		///
		int RowStretch(int row) const;

		///
		/// @brief 设置行缩放因子。
		///
		/// @param row
		/// @param stretch
		///
		void SetRowStretch(int row, int stretch);

		///
		/// @brief 列缩放因子。
		///
		/// @param column
		/// @return int
		///
		int ColumnStretch(int column) const;

		///
		/// @brief 设置列缩放因子。
		///
		/// @param column
		/// @param stretch
		///
		void SetColumnStretch(int column, int stretch);

		/* #endregion */

		/* #region 网格盒子的样式 */

		///
		/// @brief 网格盒子的对齐方式。
		///
		/// @return Qt::AlignmentFlag
		///
		Qt::AlignmentFlag Alignment() const;

		///
		/// @brief 设置网格盒子的对齐方式。
		///
		/// @note 默认是展开。即网格盒子充满整个上级容器。
		///
		/// @note 设置为 Qt::AlignmentFlag::AlignTop 可以让网格每一行都适应内容的高度，而不是整体撑开，
		/// 导致每一行都因为内容无法充满格子而有大量空白。
		///
		/// @param alignment 对齐方式。
		///
		void SetAlignment(Qt::AlignmentFlag alignment);

		///
		/// @brief 网格盒子的内边距。
		///
		/// @return widget::Padding
		///
		widget::Padding Padding() const;

		///
		/// @brief 设置网格盒子的内边距。
		///
		/// @param value
		///
		void SetPadding(widget::Padding const &value);

		/* #endregion */
	};
} // namespace widget
