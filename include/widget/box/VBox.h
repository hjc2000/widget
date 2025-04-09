#pragma once
#include "base/container/iterator/IEnumerable.h"
#include "qwidget.h"
#include "widget/layout/Padding.h"
#include "widget/layout/VBoxLayout.h"
#include <memory>
#include <set>

namespace widget
{
	///
	/// @brief 垂直布局的盒子。
	///
	///
	class VBox :
		public QWidget
	{
	private:
		widget::VBoxLayout _layout{this};
		std::set<std::shared_ptr<QWidget>> _widget_set;

	public:
		/* #region 构造函数 */

		VBox() = default;
		VBox(std::initializer_list<std::shared_ptr<QWidget>> const &widgets);
		VBox(std::vector<std::shared_ptr<QWidget>> const &widgets);
		VBox(base::IEnumerable<std::shared_ptr<QWidget>> const &widgets);

		template <size_t TCount>
		VBox(std::array<std::shared_ptr<QWidget>, TCount> const &widgets)
		{
			AddWidget(widgets);
		}

		/* #endregion */

		/* #region AddWidget */

		///
		/// @brief 向盒子添加一个控件。
		///
		/// @param widget
		///
		void AddWidget(std::shared_ptr<QWidget> const &widget);

		///
		/// @brief 向盒子添加一系列控件。
		///
		/// @param widgets
		///
		void AddWidget(std::initializer_list<std::shared_ptr<QWidget>> const &widgets);

		///
		/// @brief 向盒子添加一系列控件。
		///
		/// @param widgets
		///
		void AddWidget(std::vector<std::shared_ptr<QWidget>> const &widgets);

		///
		/// @brief 向盒子添加一系列控件。
		///
		/// @param widgets
		///
		void AddWidget(base::IEnumerable<std::shared_ptr<QWidget>> const &widgets);

		///
		/// @brief 向盒子添加一系列控件。
		///
		/// @tparam TCount
		/// @param widgets
		///
		template <size_t TCount>
		void AddWidget(std::array<std::shared_ptr<QWidget>, TCount> const &widgets)
		{
			for (auto widget : widgets)
			{
				AddWidget(widget);
			}
		}

		/* #endregion */

		///
		/// @brief 将控件从盒子中移除。
		///
		/// @param widget
		///
		void RemoveWidget(std::shared_ptr<QWidget> const &widget);

		///
		/// @brief 清空盒子中的所有控件。
		///
		///
		void ClearWidget();

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
