#include "HBoxLayout.h"

widget::HBoxLayout::HBoxLayout(QWidget *parent)
{
	_layout = std::shared_ptr<QHBoxLayout>{new QHBoxLayout{parent}};
}

void widget::HBoxLayout::AddWidget(QWidget *widget)
{
	_layout->addWidget(widget);
}
