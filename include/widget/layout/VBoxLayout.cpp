#include "VBoxLayout.h"

/* #region 构造函数 */

widget::VBoxLayout::VBoxLayout(QWidget *parent)
	: VBoxLayout(parent, widget::Padding{})
{
}

widget::VBoxLayout::VBoxLayout(QWidget *parent, widget::Padding const &padding)
{
	_layout = std::shared_ptr<QVBoxLayout>{new QVBoxLayout{parent}};

	_layout->setAlignment(Qt::Alignment{Qt::AlignmentFlag::AlignTop | Qt::AlignmentFlag::AlignLeft});

	// 控件之间的间距。
	_layout->setSpacing(10);

	SetPadding(padding);
}

/* #endregion */

void widget::VBoxLayout::AddWidget(QWidget *widget)
{
	_layout->addWidget(widget);
}

void widget::VBoxLayout::RemoveWidget(QWidget *widget)
{
	_layout->removeWidget(widget);
}

widget::Padding widget::VBoxLayout::Padding() const
{
	QMargins value = _layout->contentsMargins();

	return widget::Padding{
		value.left(),
		value.top(),
		value.right(),
		value.bottom(),
	};
}

void widget::VBoxLayout::SetPadding(widget::Padding const &value)
{
	// 布局内的内容区域与布局边框的间距。实际上相当于网页中的盒子内边距。
	_layout->setContentsMargins(value.Left(), value.Top(),
								value.Right(), value.Bottom());
}
