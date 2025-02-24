#include "FormTableItem.h"

widget::FormTableItem::FormTableItem(std::string const &label, std::shared_ptr<QWidget> const &widget)
	: _label(label),
	  _widget(widget)
{
}

std::string widget::FormTableItem::Label() const
{
	return _label;
}

std::shared_ptr<QWidget> widget::FormTableItem::Widget() const
{
	return _widget;
}
