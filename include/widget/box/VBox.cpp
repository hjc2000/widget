#include "VBox.h"

widget::VBox::VBox(std::initializer_list<std::shared_ptr<QWidget>> const &widgets)
{
	AddWidget(widgets);
}

widget::VBox::VBox(std::vector<std::shared_ptr<QWidget>> const &widgets)
{
	AddWidget(widgets);
}

widget::VBox::VBox(std::vector<std::shared_ptr<QWidget>> const &widgets, widget::Padding const &padding)
	: widget::VBox(widgets)
{
	SetPadding(padding);
}

widget::VBox::VBox(base::IEnumerable<std::shared_ptr<QWidget>> const &widgets)
{
	AddWidget(widgets);
}

void widget::VBox::AddWidget(std::shared_ptr<QWidget> const &widget)
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

void widget::VBox::RemoveWidget(std::shared_ptr<QWidget> const &widget)
{
	auto it = _widget_set.find(widget);
	if (it == _widget_set.end())
	{
		return;
	}

	_widget_set.erase(widget);
	_layout.RemoveWidget(widget.get());
}

void widget::VBox::ClearWidget()
{
	for (auto widget : _widget_set)
	{
		_layout.RemoveWidget(widget.get());
	}

	_widget_set.clear();
}

widget::Padding widget::VBox::Padding() const
{
	return _layout.Padding();
}

void widget::VBox::SetPadding(widget::Padding const &value)
{
	_layout.SetPadding(value);
}
