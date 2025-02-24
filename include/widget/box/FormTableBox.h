#pragma once
#include "qwidget.h"
#include "widget/layout/Padding.h"
#include <base/container/Dictionary.h>
#include <initializer_list>
#include <widget/box/FormTableBoxItem.h>
#include <widget/layout/FormTableLayout.h>

namespace widget
{
	/**
	 * @brief 表单布局的盒子。
	 *
	 */
	class FormTableBox :
		public QWidget
	{
	private:
		widget::FormTableLayout _layout{this, widget::Padding{10}};
		base::Dictionary<int, widget::FormTableBoxItem> _widget_dic;

	public:
		/**
		 * @brief Construct a new Form Table Box object
		 *
		 */
		FormTableBox() = default;

		/**
		 * @brief Construct a new Form Table Box object
		 *
		 * @param items
		 */
		FormTableBox(std::initializer_list<widget::FormTableBoxItem> const &items);

	public:
		/**
		 * @brief 设置一条表单项。
		 *
		 * @param row
		 * @param item
		 */
		void SetItem(int row, widget::FormTableBoxItem const &item);

		/**
		 * @brief 设置一系列表单项。
		 *
		 * @param items
		 */
		void SetItem(std::initializer_list<widget::FormTableBoxItem> const &items);

		/**
		 * @brief 移除某一行。
		 *
		 * @param row
		 */
		void RemoveItem(int row);
	};
} // namespace widget
