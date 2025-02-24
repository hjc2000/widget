#include "FormTableBoxItem.h"

widget::FormTableBoxItem::FormTableBoxItem(std::string const &label, std::shared_ptr<QWidget> const &widget)
	: _label(label),
	  _widget(widget)
{
}

std::string widget::FormTableBoxItem::Label() const
{
	return _label;
}

std::shared_ptr<QWidget> widget::FormTableBoxItem::Widget() const
{
	return _widget;
}
