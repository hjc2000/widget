#include "FormTableBox.h"
#include <base/string/define.h>
#include <exception>
#include <stdexcept>

widget::FormTableBox::FormTableBox(std::initializer_list<widget::FormTableBoxItem> const &items)
{
	try
	{
		SetItem(items);
	}
	catch (std::exception const &e)
	{
		throw new std::runtime_error{CODE_POS_STR + e.what()};
	}
}

void widget::FormTableBox::SetItem(int row, std::string const &label, std::shared_ptr<QWidget> const &widget)
{
	if (widget == nullptr)
	{
		throw std::invalid_argument{CODE_POS_STR + "widget 不能是空指针"};
	}

	_layout.SetItem(row, label, widget.get());
	_widget_dic.Add(row, widget);
}

void widget::FormTableBox::SetItem(int row, widget::FormTableBoxItem const &item)
{
	try
	{
		SetItem(row, item.Label(), item.Widget());
	}
	catch (std::exception const &e)
	{
		throw new std::runtime_error{CODE_POS_STR + e.what()};
	}
}

void widget::FormTableBox::SetItem(std::initializer_list<widget::FormTableBoxItem> const &items)
{
	try
	{
		int i = 0;
		for (widget::FormTableBoxItem const &item : items)
		{
			SetItem(i++, item);
		}
	}
	catch (std::exception const &e)
	{
		throw new std::runtime_error{CODE_POS_STR + e.what()};
	}
}

void widget::FormTableBox::RemoveItem(int row)
{
	_layout.RemoveItem(row);
	_widget_dic.Remove(row);
}
