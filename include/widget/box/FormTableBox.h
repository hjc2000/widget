#pragma once
#include "base/container/Dictionary.h"
#include "QWidget"
#include "widget/box/FormTableBoxItem.h"
#include "widget/layout/FormTableLayout.h"
#include "widget/layout/Padding.h"

namespace widget
{
	///
	/// @brief 表单布局的盒子。
	///
	///
	class FormTableBox :
		public QWidget
	{
	private:
		widget::FormTableLayout _layout{this, widget::Padding{0}};
		base::Dictionary<int, widget::FormTableBoxItem> _widget_dic;

	public:
		FormTableBox() = default;
		FormTableBox(std::initializer_list<widget::FormTableBoxItem> const &items);

		///
		/// @brief 设置一条表单项。
		///
		/// @param row 要将表单项设置到哪一行。
		///		@note 如果该行已经有表单项了，会先移除旧的表单项。
		///
		/// @param item
		///
		void SetItem(int row, widget::FormTableBoxItem const &item);

		///
		/// @brief 设置一系列表单项。
		///
		/// @note 从第 0 行开始添加，如果添加到某一行，该行已经有一个表单项了，则会先移除旧的
		/// 表单项，然后添加。
		///
		/// @param items
		///
		void SetItem(std::initializer_list<widget::FormTableBoxItem> const &items);

		///
		/// @brief 移除某一行的表单项。
		///
		/// @param row
		///
		void RemoveItem(int row);

		void ClearItems();

		///
		/// @brief 表单盒子内边距。
		///
		/// @return widget::Padding
		///
		widget::Padding Padding() const;

		///
		/// @brief 设置表单盒子内边距。
		///
		/// @param value
		///
		void SetPadding(widget::Padding const &value);
	};
} // namespace widget
