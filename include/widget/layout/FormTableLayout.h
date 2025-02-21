#pragma once
#include "qwidget.h"
#include <widget/layout/GridLayout.h>

namespace widget
{
	/**
	 * @brief 表单布局。
	 *
	 */
	class FormTableLayout
	{
	public:
		FormTableLayout(QWidget *parent);

	public:
		/**
		 * @brief 设置一条表单项。
		 *
		 * @param row
		 * @param label
		 * @param widget
		 */
		void SetItem(int row, std::string const &label, QWidget *widget);
	};
} // namespace widget
