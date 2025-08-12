#pragma once
#include "QBoxLayout"
#include "widget/layout/Padding.h"

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
		QHBoxLayout *_layout;

	public:
		///
		/// @brief 构造一个水平布局的盒子。
		///
		/// @param parent 要被布局控件进行 UI 布局的 QWidget 对象。
		///
		HBoxLayout(QWidget *parent)
		{
			_layout = new QHBoxLayout{parent};

			_layout->setAlignment(Qt::Alignment{Qt::AlignmentFlag::AlignTop | Qt::AlignmentFlag::AlignLeft});

			// 控件之间的间距。
			_layout->setSpacing(10);

			SetPadding(widget::Padding{});
		}

		///
		/// @brief 构造一个水平布局的盒子。
		///
		/// @param parent 要被布局控件进行 UI 布局的 QWidget 对象。
		/// @param paddint 盒子内边距。
		///
		HBoxLayout(QWidget *parent, widget::Padding const &paddint)
			: widget::HBoxLayout{parent}
		{
			SetPadding(paddint);
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
