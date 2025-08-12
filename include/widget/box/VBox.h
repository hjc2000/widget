#pragma once
#include "base/container/iterator/IEnumerable.h"
#include "base/string/define.h"
#include "qwidget.h"
#include "widget/layout/Padding.h"
#include "widget/layout/VBoxLayout.h"
#include <memory>

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

	public:
		/* #region 构造函数 */

		VBox() = default;

		VBox(std::initializer_list<std::shared_ptr<QWidget>> const &widgets)
		{
			AddWidget(widgets);
		}

		VBox(std::vector<std::shared_ptr<QWidget>> const &widgets)
		{
			AddWidget(widgets);
		}

		VBox(base::IEnumerable<std::shared_ptr<QWidget>> const &widgets)
		{
			AddWidget(widgets);
		}

		template <size_t TCount>
		VBox(std::array<std::shared_ptr<QWidget>, TCount> const &widgets)
		{
			AddWidget(widgets);
		}

		~VBox()
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

			_layout.AddWidget(widget);
		}

		///
		/// @brief 向盒子添加一系列控件。
		///
		/// @param widgets
		///
		void AddWidget(std::initializer_list<std::shared_ptr<QWidget>> const &widgets)
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
			_layout.RemoveWidget(widget);
		}

		///
		/// @brief 清空盒子中的所有控件。
		///
		///
		void ClearWidget()
		{
			_layout.ClearWidget();
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
