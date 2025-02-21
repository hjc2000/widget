#include "IBox.h"

void widget::IBox::AddWidget(std::initializer_list<std::shared_ptr<QWidget>> widgets)
{
	for (auto widget : widgets)
	{
		AddWidget(widget);
	}
}

void widget::IBox::AddWidget(std::vector<std::shared_ptr<QWidget>> widgets)
{
	for (auto widget : widgets)
	{
		AddWidget(widget);
	}
}

void widget::IBox::AddWidget(base::IEnumerable<std::shared_ptr<QWidget>> &widgets)
{
	for (auto widget : widgets)
	{
		AddWidget(widget);
	}
}
