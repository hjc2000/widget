#pragma once
#include "qwidget.h"
#include "widget/layout/Padding.h"
#include <memory>

namespace widget
{
	class IBox :
		public QWidget
	{
	public:
		/**
		 * @brief 向盒子添加一个控件。
		 *
		 * @param widget
		 */
		virtual void AddWidget(std::shared_ptr<QWidget> widget) = 0;

		/**
		 * @brief 将控件从盒子中移除。
		 *
		 * @param widget
		 */
		virtual void RemoveWidget(std::shared_ptr<QWidget> widget) = 0;

		/**
		 * @brief 清空盒子中的所有控件。
		 *
		 */
		virtual void ClearWidget() = 0;

	public:
		/**
		 * @brief 获取内边距。
		 *
		 * @return widget::Padding
		 */
		virtual widget::Padding Padding() const = 0;

		/**
		 * @brief 设置内边距。
		 *
		 * @param value
		 */
		virtual void SetPadding(widget::Padding const &value) = 0;

	public:
		/**
		 * @brief 向盒子添加一系列控件。
		 *
		 * @param widget_list
		 */
		void AddWidget(std::initializer_list<std::shared_ptr<QWidget>> widget_list);
	};
} // namespace widget
