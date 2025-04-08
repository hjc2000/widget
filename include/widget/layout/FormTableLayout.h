#pragma once
#include "widget/layout/GridLayout.h"

namespace widget
{
	///
	/// @brief 表单布局。
	///
	///
	class FormTableLayout
	{
	private:
		std::shared_ptr<widget::GridLayout> _grid_layout;

		void Initialize();

	public:
		/* #region 构造函数 */

		///
		/// @brief 构造函数。
		///
		/// @param parent 要被表单布局接管 UI 布局的父控件。
		///
		FormTableLayout(QWidget *parent);

		///
		/// @brief 构造函数。
		///
		/// @param parent 要被表单布局接管 UI 布局的父控件。
		/// @param padding 表单盒子的内边距。
		///
		FormTableLayout(QWidget *parent, widget::Padding const &padding);

		/* #endregion */

		///
		/// @brief 设置一条表单项。
		///
		/// @param row 要将表单项设置在哪一行。
		/// @param left 表单项左侧控件。宽度根据内容调整。
		/// @param right 表单项右侧控件。宽度充满剩余宽度。
		///
		void SetItem(int row, QWidget *left, QWidget *right);

		///
		/// @brief 移除一条表单项。
		///
		/// @param row 要移除哪一行的表单项。
		///
		void RemoveItem(int row);

		///
		/// @brief 清除表单布局中的所有表单项。
		///
		///
		void ClearItems();

		/* #region 样式 */

		///
		/// @brief 表单布局内边距。
		///
		/// @return widget::Padding
		///
		widget::Padding Padding() const;

		///
		/// @brief 设置表单布局内边距。
		///
		/// @param value
		///
		void SetPadding(widget::Padding const &value);

		/* #endregion */
	};
} // namespace widget
