#pragma once
#include "qboxlayout.h"
#include "widget/layout/Padding.h"
#include <memory>

namespace widget
{
	///
	/// @brief 垂直盒子布局。
	/// 	@li 左对齐，顶端对齐。
	/// 	@li 盒子内元素间距 10.
	/// 	@li 盒子内边距为 0.
	///
	class VBoxLayout
	{
	private:
		std::shared_ptr<QVBoxLayout> _layout;

	public:
		///
		/// @brief
		///
		/// @param parent 要被布局控件进行 UI 布局的 QWidget 对象。
		///
		VBoxLayout(QWidget *parent)
			: VBoxLayout(parent, widget::Padding{})
		{
		}

		///
		/// @brief
		///
		/// @param parent 要被布局控件进行 UI 布局的 QWidget 对象。
		/// @param padding 盒子内边距。
		///
		VBoxLayout(QWidget *parent, widget::Padding const &padding)
		{
			_layout = std::shared_ptr<QVBoxLayout>{new QVBoxLayout{parent}};

			_layout->setAlignment(Qt::Alignment{Qt::AlignmentFlag::AlignTop | Qt::AlignmentFlag::AlignLeft});

			// 控件之间的间距。
			_layout->setSpacing(10);

			SetPadding(padding);
		}

		~VBoxLayout()
		{
			_layout->setParent(nullptr);
		}

		///
		/// @brief 向布局添加一个控件。
		///
		/// @param widget 要被添加到布局中进行显示的 QWidget 对象。
		///
		void AddWidget(QWidget *widget)
		{
			_layout->addWidget(widget);
		}

		///
		/// @brief 将控件从布局中移除。
		///
		/// @param widget
		///
		void RemoveWidget(QWidget *widget)
		{
			_layout->removeWidget(widget);
		}

		///
		/// @brief 获取内边距。
		///
		/// @return widget::Padding
		///
		widget::Padding Padding() const
		{
			QMargins value = _layout->contentsMargins();

			return widget::Padding{
				value.left(),
				value.top(),
				value.right(),
				value.bottom(),
			};
		}

		///
		/// @brief 设置内边距。
		///
		/// @param value
		///
		void SetPadding(widget::Padding const &value)
		{
			// 布局内的内容区域与布局边框的间距。实际上相当于网页中的盒子内边距。
			_layout->setContentsMargins(value.Left(), value.Top(),
										value.Right(), value.Bottom());
		}
	};

} // namespace widget
