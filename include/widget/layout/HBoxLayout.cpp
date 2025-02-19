#include "HBoxLayout.h"

widget::HBoxLayout::HBoxLayout(QWidget *parent)
{
	_layout = std::shared_ptr<QHBoxLayout>{new QHBoxLayout{parent}};
}

void widget::HBoxLayout::AddWidget(QWidget *widget)
{
	_layout->addWidget(widget);
	_layout->setAlignment(Qt::Alignment{Qt::AlignmentFlag::AlignTop | Qt::AlignmentFlag::AlignLeft});

	// 控件之间的间距。
	_layout->setSpacing(10);

	// 布局内的内容区域与布局边框的间距。实际上相当于网页中的盒子内边距。
	_layout->setContentsMargins(0, 0, 0, 0);
}
