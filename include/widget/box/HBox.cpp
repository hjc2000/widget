#include "HBox.h"

void widget::HBox::AddWidget(std::shared_ptr<QWidget> widget)
{
	auto it = _widget_set.find(widget);
	if (it != _widget_set.end())
	{
		// 如果已经添加过了，就不重复添加了。
		return;
	}

	_widget_set.insert(widget);
	_layout.AddWidget(widget.get());
}

void widget::HBox::RemoveWidget(std::shared_ptr<QWidget> widget)
{
	auto it = _widget_set.find(widget);
	if (it == _widget_set.end())
	{
		return;
	}

	_widget_set.erase(widget);
	_layout.RemoveWidget(widget.get());
}

void widget::HBox::ClearWidget()
{
	for (auto widget : _widget_set)
	{
		_layout.RemoveWidget(widget.get());
	}

	_widget_set.clear();
}

widget::Padding widget::HBox::Padding() const
{
	return _layout.Padding();
}

void widget::HBox::SetPadding(widget::Padding const &value)
{
	_layout.SetPadding(value);
}
