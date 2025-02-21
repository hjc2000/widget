#pragma once
#include "qwidget.h"
#include <initializer_list>
#include <memory>
#include <set>
#include <widget/box/IBox.h>
#include <widget/layout/VBoxLayout.h>

namespace widget
{
	/**
	 * @brief 垂直布局的盒子。
	 *
	 */
	class VBox :
		public widget::IBox
	{
	private:
		widget::VBoxLayout _layout{this};
		std::set<std::shared_ptr<QWidget>> _widget_set;

	public:
		/**
		 * @brief Construct a new VBox object
		 *
		 */
		VBox();

		/**
		 * @brief Construct a new VBox object
		 *
		 * @param widget_list
		 */
		VBox(std::initializer_list<std::shared_ptr<QWidget>> widget_list);

	public:
		using IBox::AddWidget;

		/**
		 * @brief 向盒子添加一个控件。
		 *
		 * @param widget
		 */
		virtual void AddWidget(std::shared_ptr<QWidget> widget) override;

		/**
		 * @brief 将控件从盒子中移除。
		 *
		 * @param widget
		 */
		virtual void RemoveWidget(std::shared_ptr<QWidget> widget) override;

		/**
		 * @brief 清空盒子中的所有控件。
		 *
		 */
		virtual void ClearWidget() override;

	public:
		/**
		 * @brief 获取内边距。
		 *
		 * @return widget::Padding
		 */
		virtual widget::Padding Padding() const override;

		/**
		 * @brief 设置内边距。
		 *
		 * @param value
		 */
		virtual void SetPadding(widget::Padding const &value) override;
	};
} // namespace widget
