#pragma once
#include "qwidget.h"
#include "widget/layout/Padding.h"
#include <initializer_list>
#include <widget/layout/FormTableItem.h>
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

	public:
		FormTableBox() = default;

		FormTableBox(std::initializer_list<widget::FormTableItem> items)
		{
		}

	public:
		/**
		 * @brief 设置一条表单项。
		 *
		 * @param row
		 * @param label
		 * @param widget
		 */
		void SetItem(int row, std::string const &label, QWidget *widget);

		void SetItem(std::initializer_list<widget::FormTableItem> items);

		/**
		 * @brief 移除某一行。
		 *
		 * @param row
		 */
		void RemoveItem(int row);
	};
} // namespace widget
