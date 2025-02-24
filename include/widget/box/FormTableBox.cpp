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

void widget::FormTableBox::SetItem(int row, widget::FormTableBoxItem const &item)
{
	if (item.Left() == nullptr)
	{
		throw new std::runtime_error{CODE_POS_STR + "item.Left() 不能为空指针。"};
	}

	if (item.Right() == nullptr)
	{
		throw new std::runtime_error{CODE_POS_STR + "item.Right() 不能为空指针。"};
	}

	try
	{
		_layout.SetItem(row, item.Left().get(), item.Right().get());
		_widget_dic.Add(row, item);
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
