#include "HBoxLayout.h"

widget::HBoxLayout::HBoxLayout(QWidget *parent)
{
	_layout = std::shared_ptr<QHBoxLayout>{new QHBoxLayout{parent}};

	_layout->setAlignment(Qt::Alignment{Qt::AlignmentFlag::AlignTop | Qt::AlignmentFlag::AlignLeft});

	// 控件之间的间距。
	_layout->setSpacing(10);

	SetPadding(widget::Padding{});
}

widget::HBoxLayout::HBoxLayout(QWidget *parent, widget::Padding const &paddint)
	: widget::HBoxLayout{parent}
{
	SetPadding(paddint);
}

void widget::HBoxLayout::AddWidget(QWidget *widget)
{
	_layout->addWidget(widget);
}

void widget::HBoxLayout::RemoveWidget(QWidget *widget)
{
	_layout->removeWidget(widget);
}

widget::Padding widget::HBoxLayout::Padding() const
{
	QMargins value = _layout->contentsMargins();

	return widget::Padding{
		value.left(),
		value.top(),
		value.right(),
		value.bottom(),
	};
}

void widget::HBoxLayout::SetPadding(widget::Padding const &value)
{
	// 布局内的内容区域与布局边框的间距。实际上相当于网页中的盒子内边距。
	_layout->setContentsMargins(value.Left(), value.Top(),
								value.Right(), value.Bottom());
}
