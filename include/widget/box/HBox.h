#pragma once
#include "IBox.h"
#include <set>
#include <widget/box/IBox.h>
#include <widget/layout/HBoxLayout.h>

namespace widget
{
	class HBox :
		public widget::IBox
	{
	private:
		widget::HBoxLayout _layout{this};
		std::set<std::shared_ptr<QWidget>> _widget_set;

	public:
		/* #region 构造函数 */

		HBox() = default;
		HBox(std::initializer_list<std::shared_ptr<QWidget>> const &widgets);
		HBox(std::vector<std::shared_ptr<QWidget>> const &widgets);
		HBox(std::vector<std::shared_ptr<QWidget>> const &widgets, widget::Padding const &padding);
		HBox(base::IEnumerable<std::shared_ptr<QWidget>> const &widgets);

		template <size_t TCount>
		HBox(std::array<std::shared_ptr<QWidget>, TCount> const &widgets)
		{
			AddWidget(widgets);
		}

		/* #endregion */

		using IBox::AddWidget;

		///
		/// @brief 向盒子添加一个控件。
		///
		/// @param widget
		///
		virtual void AddWidget(std::shared_ptr<QWidget> const &widget) override;

		///
		/// @brief 将控件从盒子中移除。
		///
		/// @param widget
		///
		virtual void RemoveWidget(std::shared_ptr<QWidget> const &widget) override;

		///
		/// @brief 清空盒子中的所有控件。
		///
		///
		virtual void ClearWidget() override;

		///
		/// @brief 获取内边距。
		///
		/// @return widget::Padding
		///
		virtual widget::Padding Padding() const override;

		///
		/// @brief 设置内边距。
		///
		/// @param value
		///
		virtual void SetPadding(widget::Padding const &value) override;
	};
} // namespace widget
