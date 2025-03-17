#include "FormTableBox.h"

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
	if (item.LeftWidget() == nullptr)
	{
		throw new std::runtime_error{CODE_POS_STR + "item.LeftWidget() 不能为空指针。"};
	}

	if (item.RightWidget() == nullptr)
	{
		throw new std::runtime_error{CODE_POS_STR + "item.RightWidget() 不能为空指针。"};
	}

	try
	{
		_layout.SetItem(row, item.LeftWidget().get(), item.RightWidget().get());
		_widget_dic.Add(row, item);
	}
	catch (std::exception const &e)
	{
		throw new std::runtime_error{CODE_POS_STR + e.what()};
	}
}

void widget::FormTableBox::SetItem(std::initializer_list<widget::FormTableBoxItem> const &items)
{
	int i = 0;

	try
	{
		for (widget::FormTableBoxItem const &item : items)
		{
			SetItem(i++, item);
		}
	}
	catch (std::exception const &e)
	{
		std::string message = CODE_POS_STR +
							  std::format("添加到第 {} 个项目时引发异常", i) +
							  e.what();

		throw new std::runtime_error{message};
	}
}

void widget::FormTableBox::RemoveItem(int row)
{
	_layout.RemoveItem(row);
	_widget_dic.Remove(row);
}

widget::Padding widget::FormTableBox::Padding() const
{
	return _layout.Padding();
}

void widget::FormTableBox::SetPadding(widget::Padding const &value)
{
	_layout.SetPadding(value);
}
