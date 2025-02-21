#include "IBox.h"

void widget::IBox::AddWidget(std::initializer_list<std::shared_ptr<QWidget>> widget_list)
{
	for (auto widget : widget_list)
	{
		AddWidget(widget);
	}
}
