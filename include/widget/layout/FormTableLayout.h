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
		FormTableLayout(QWidget *parent);
		FormTableLayout(QWidget *parent, widget::Padding const &padding);

		///
		/// @brief 设置一条表单项。
		///
		/// @param row
		/// @param left
		/// @param right
		///
		void SetItem(int row, QWidget *left, QWidget *right);

		///
		/// @brief 移除某一行。
		///
		/// @param row
		///
		void RemoveItem(int row);

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
	};
} // namespace widget
