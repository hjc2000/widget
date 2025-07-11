#include "VBox.h"
#include "base/string/define.h"

/* #region 构造函数 */

widget::VBox::VBox(std::initializer_list<std::shared_ptr<QWidget>> const &widgets)
{
	AddWidget(widgets);
}

widget::VBox::VBox(std::vector<std::shared_ptr<QWidget>> const &widgets)
{
	AddWidget(widgets);
}

widget::VBox::VBox(base::IEnumerable<std::shared_ptr<QWidget>> const &widgets)
{
	AddWidget(widgets);
}

/* #endregion */

/* #region AddWidget */

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

void widget::VBox::AddWidget(std::initializer_list<std::shared_ptr<QWidget>> const &widgets)
{
	for (auto widget : widgets)
	{
		AddWidget(widget);
	}
}

void widget::VBox::AddWidget(std::vector<std::shared_ptr<QWidget>> const &widgets)
{
	for (auto widget : widgets)
	{
		AddWidget(widget);
	}
}

void widget::VBox::AddWidget(base::IEnumerable<std::shared_ptr<QWidget>> const &widgets)
{
	for (auto widget : widgets)
	{
		AddWidget(widget);
	}
}

/* #endregion */

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
