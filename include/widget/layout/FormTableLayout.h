#pragma once
#include "Padding.h"
#include "qwidget.h"
#include <memory>
#include <widget/layout/GridLayout.h>

namespace widget
{
	/**
	 * @brief 表单布局。
	 *
	 */
	class FormTableLayout
	{
	private:
		std::shared_ptr<widget::GridLayout> _grid_layout;

		void Initialize();

	public:
		/**
		 * @brief Construct a new Form Table Layout object
		 *
		 * @param parent
		 */
		FormTableLayout(QWidget *parent);

		/**
		 * @brief Construct a new Form Table Layout object
		 *
		 * @param parent
		 * @param padding
		 */
		FormTableLayout(QWidget *parent, widget::Padding const &padding);

	public:
		/**
		 * @brief 设置一条表单项。
		 *
		 * @param row
		 * @param left
		 * @param right
		 */
		void SetItem(int row, QWidget *left, QWidget *right);

		/**
		 * @brief 移除某一行。
		 *
		 * @param row
		 */
		void RemoveItem(int row);
	};
} // namespace widget
