#include "FormTableBox.h"

widget::FormTableBox::FormTableBox(std::initializer_list<widget::FormTableItem> items)
{
	SetItem(items);
}

void widget::FormTableBox::SetItem(int row, std::string const &label, QWidget *widget)
{
	_layout.SetItem(row, label, widget);
}

void widget::FormTableBox::SetItem(int row, widget::FormTableItem const &item)
{
	SetItem(row, item.Label(), item.Widget());
}

void widget::FormTableBox::SetItem(std::initializer_list<widget::FormTableItem> items)
{
	int i = 0;
	for (widget::FormTableItem const &item : items)
	{
		SetItem(i++, item);
	}
}

void widget::FormTableBox::RemoveItem(int row)
{
	_layout.RemoveItem(row);
}
