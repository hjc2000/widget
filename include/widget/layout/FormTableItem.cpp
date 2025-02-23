#include "FormTableItem.h"

widget::FormTableItem::FormTableItem(std::string const &label, QWidget *widget)
	: _label(label),
	  _widget(widget)
{
}

std::string widget::FormTableItem::Label() const
{
	return _label;
}

QWidget *widget::FormTableItem::Widget() const
{
	return _widget;
}
