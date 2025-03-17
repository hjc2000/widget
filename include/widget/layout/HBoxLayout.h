#pragma once
#include <qboxlayout.h>
#include <widget/layout/Padding.h>

namespace widget
{
	///
	/// @brief 自定义了样式的水平盒子布局。
	/// 	@li 左对齐，顶端对齐。
	/// 	@li 盒子内元素间距 10.
	/// 	@li 盒子内边距为 0.
	///
	class HBoxLayout
	{
	private:
		std::shared_ptr<QHBoxLayout> _layout;

	public:
		///
		/// @brief 构造一个水平布局的盒子。
		///
		/// @param parent 要被布局控件进行 UI 布局的 QWidget 对象。
		///
		HBoxLayout(QWidget *parent);

		///
		/// @brief 构造一个水平布局的盒子。
		///
		/// @param parent 要被布局控件进行 UI 布局的 QWidget 对象。
		/// @param paddint 盒子内边距。
		///
		HBoxLayout(QWidget *parent, widget::Padding const &paddint);

		///
		/// @brief 向布局添加一个控件。
		///
		/// @param widget 要被添加到布局中进行显示的 QWidget 对象。
		///
		void AddWidget(QWidget *widget);

		///
		/// @brief 将控件从布局中移除。
		///
		/// @param widget
		///
		void RemoveWidget(QWidget *widget);

		///
		/// @brief 获取内边距。
		///
		/// @return widget::Padding
		///
		widget::Padding Padding() const;

		///
		/// @brief 设置内边距。
		///
		/// @param value
		///
		void SetPadding(widget::Padding const &value);
	};
} // namespace widget
