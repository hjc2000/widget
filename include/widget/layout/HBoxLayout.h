#pragma once
#include <cwchar>
#include <memory>
#include <qboxlayout.h>
#include <qwidget.h>

namespace widget
{
	/**
	 * @brief 自定义了样式的水平盒子布局。
	 * @li 左对齐，顶端对齐。
	 * @li 盒子内元素间距 10.
	 * @li 盒子内边距为 0.
	 */
	class HBoxLayout
	{
	private:
		std::shared_ptr<QHBoxLayout> _layout;

	public:
		/**
		 * @brief Construct a new HBoxLayout object
		 *
		 * @param parent 要被布局控件进行 UI 布局的 QWidget 对象。
		 */
		HBoxLayout(QWidget *parent);

		/**
		 * @brief 向布局添加一个控件。
		 *
		 * @param widget 要被添加到布局中进行显示的 QWidget 对象。
		 */
		void AddWidget(QWidget *widget);
	};
} // namespace widget
