#include "VBox.h"
#include "base/string/define.h"

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
