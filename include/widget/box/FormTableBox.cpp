#include "FormTableBox.h"

void widget::FormTableBox::SetItem(int row, std::string const &label, QWidget *widget)
{
	_layout.SetItem(row, label, widget);
}

void widget::FormTableBox::RemoveItem(int row)
{
	_layout.RemoveItem(row);
}

void widget::FormTableBox::SetItem(std::initializer_list<widget::FormTableItem> items)
{
	int i = 0;
	for (widget::FormTableItem const &item : items)
	{
		SetItem(i++, item.Label(), item.Widget());
	}
}
