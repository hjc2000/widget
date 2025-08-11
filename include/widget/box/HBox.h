#pragma once
#include "base/container/iterator/IEnumerable.h"
#include "base/string/define.h"
#include "qwidget.h"
#include "widget/layout/HBoxLayout.h"
#include "widget/layout/Padding.h"
#include <memory>
#include <set>

namespace widget
{
	class HBox final :
		public QWidget
	{
	private:
		widget::HBoxLayout _layout{this};
		std::set<std::shared_ptr<QWidget>> _widget_set;

	public:
		/* #region 构造函数 */

		HBox() = default;

		HBox(std::initializer_list<std::shared_ptr<QWidget>> const &widgets)
		{
			AddWidget(widgets);
		}

		HBox(std::vector<std::shared_ptr<QWidget>> const &widgets)
		{
			AddWidget(widgets);
		}

		HBox(base::IEnumerable<std::shared_ptr<QWidget>> const &widgets)
		{
			AddWidget(widgets);
		}

		template <size_t TCount>
		HBox(std::array<std::shared_ptr<QWidget>, TCount> const &widgets)
		{
			AddWidget(widgets);
		}

		~HBox()
		{
			ClearWidget();
		}

		/* #endregion */

		/* #region AddWidget */

		///
		/// @brief 向盒子添加一个控件。
		///
		/// @param widget
		///
		void AddWidget(std::shared_ptr<QWidget> const &widget)
		{
			if (widget == nullptr)
			{
				throw std::invalid_argument{CODE_POS_STR + "widget 不能是空指针"};
			}

			auto it = _widget_set.find(widget);
			if (it != _widget_set.end())
			{
				// 如果已经添加过了，就不重复添加了。
				return;
			}

			_widget_set.insert(widget);
			_layout.AddWidget(widget.get());
		}

		///
		/// @brief 向盒子添加一系列控件。
		///
		/// @param widgets
		///
		void AddWidget(std::initializer_list<std::shared_ptr<QWidget>> const &widgets)
		{
			for (std::shared_ptr<QWidget> const &widget : widgets)
			{
				AddWidget(widget);
			}
		}

		///
		/// @brief 向盒子添加一系列控件。
		///
		/// @param widgets
		///
		void AddWidget(std::vector<std::shared_ptr<QWidget>> const &widgets)
		{
			for (auto widget : widgets)
			{
				AddWidget(widget);
			}
		}

		///
		/// @brief 向盒子添加一系列控件。
		///
		/// @param widgets
		///
		void AddWidget(base::IEnumerable<std::shared_ptr<QWidget>> const &widgets)
		{
			for (auto widget : widgets)
			{
				AddWidget(widget);
			}
		}

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
		void RemoveWidget(std::shared_ptr<QWidget> const &widget)
		{
			auto it = _widget_set.find(widget);
			if (it == _widget_set.end())
			{
				return;
			}

			widget->setParent(nullptr);
			_widget_set.erase(widget);
		}

		///
		/// @brief 清空盒子中的所有控件。
		///
		///
		void ClearWidget()
		{
			for (auto widget : _widget_set)
			{
				widget->setParent(nullptr);
			}

			_widget_set.clear();
		}

		///
		/// @brief 获取内边距。
		///
		/// @return
		///
		widget::Padding Padding() const
		{
			return _layout.Padding();
		}

		///
		/// @brief 设置内边距。
		///
		/// @param value
		///
		void SetPadding(widget::Padding const &value)
		{
			_layout.SetPadding(value);
		}
	};

} // namespace widget
