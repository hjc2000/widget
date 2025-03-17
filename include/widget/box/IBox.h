#pragma once
#include "qwidget.h"
#include "widget/layout/Padding.h"
#include <base/container/iterator/IEnumerable.h>
#include <memory>

namespace widget
{
	///
	/// @brief 盒子接口。
	///
	///
	class IBox :
		public QWidget
	{
	public:
		///
		/// @brief 向盒子添加一个控件。
		///
		/// @param widget
		///
		virtual void AddWidget(std::shared_ptr<QWidget> const &widget) = 0;

		///
		/// @brief 将控件从盒子中移除。
		///
		/// @param widget
		///
		virtual void RemoveWidget(std::shared_ptr<QWidget> const &widget) = 0;

		///
		/// @brief 清空盒子中的所有控件。
		///
		///
		virtual void ClearWidget() = 0;

		///
		/// @brief 获取内边距。
		///
		/// @return widget::Padding
		///
		virtual widget::Padding Padding() const = 0;

		///
		/// @brief 设置内边距。
		///
		/// @param value
		///
		virtual void SetPadding(widget::Padding const &value) = 0;

		/* #region AddWidget 扩展 */

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
	};
} // namespace widget
