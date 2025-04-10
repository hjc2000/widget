#pragma once
#include "base/container/List.h"
#include "GridBoxItem.h"
#include "LabelValueUnitGridItem.h"
#include "qgridlayout.h"
#include "qwidget.h"
#include "widget/layout/Padding.h"
#include <initializer_list>
#include <memory>
#include <vector>

namespace widget
{
	///
	/// @brief 网格盒子。
	///
	///
	class GridBox :
		public QWidget
	{
	private:
		QGridLayout _grid_layout{this};
		base::List<widget::GridBoxItem> _item_list{};

	public:
		/* #region 构造函数 */

		GridBox();

		GridBox(std::initializer_list<widget::GridBoxItem> const &items);

		GridBox(std::initializer_list<widget::LabelValueUnitGridItem> const &items);

		/* #endregion */

		void AddItem(widget::GridBoxItem const &item);

		void AddItem(widget::LabelValueUnitGridItem const &item);

		///
		/// @brief 设置一个项目。会移除同一个格子中的旧项目，然后才添加 item.
		///
		/// @param item
		///
		void SetItem(widget::GridBoxItem const &item);

		/* #region 移除控件 */

		///
		/// @brief 通过行列移除控件。
		///
		/// @param row
		/// @param column
		///
		void RemoveWidget(int row, int column);

		///
		/// @brief 移除控件。
		///
		/// @param widget
		///
		void RemoveWidget(std::shared_ptr<QWidget> widget);

		///
		/// @brief 清空所有控件。
		///
		///
		void ClearWidgets();

		/* #endregion */

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
		/// @brief 批量设置行缩放因子。
		///
		/// @param stretch_vec
		///
		void SetRowStretch(std::vector<int> const &stretch_vec);

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

		///
		/// @brief 批量设置列缩放因子。
		///
		/// @param stretch_vec
		///
		void SetColumnStretch(std::vector<int> const &stretch_vec);

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
