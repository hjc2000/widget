#pragma once
#include <memory>
#include <qboxlayout.h>
#include <widget/layout/Padding.h>

namespace widget
{
	/**
	 * @brief 自定义了样式的垂直盒子布局。
	 * 		@li 左对齐，顶端对齐。
	 * 		@li 盒子内元素间距 10.
	 * 		@li 盒子内边距为 0.
	 */
	class VBoxLayout
	{
	private:
		std::shared_ptr<QVBoxLayout> _layout;

	public:
		/**
		 * @brief Construct a new VBoxLayout object
		 *
		 * @param parent 要被布局控件进行 UI 布局的 QWidget 对象。
		 */
		VBoxLayout(QWidget *parent);

		/**
		 * @brief Construct a new VBoxLayout object
		 *
		 * @param parent 要被布局控件进行 UI 布局的 QWidget 对象。
		 * @param padding 盒子内边距。
		 */
		VBoxLayout(QWidget *parent, widget::Padding const &padding);

	public:
		/**
		 * @brief 向布局添加一个控件。
		 *
		 * @param widget 要被添加到布局中进行显示的 QWidget 对象。
		 */
		void AddWidget(QWidget *widget);

		/**
		 * @brief 将控件从布局中移除。
		 *
		 * @param widget
		 */
		void RemoveWidget(QWidget *widget);

		/**
		 * @brief 获取内边距。
		 *
		 * @return widget::Padding
		 */
		widget::Padding Padding() const;

		/**
		 * @brief 设置内边距。
		 *
		 * @param value
		 */
		void SetPadding(widget::Padding const &value);
	};
} // namespace widget
