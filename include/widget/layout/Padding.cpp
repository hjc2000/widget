#include "Padding.h"

widget::Padding::Padding(int value)
	: Padding(value, value, value, value)
{
}

widget::Padding::Padding(int left, int top, int right, int bottom)
	: _left(left),
	  _top(top),
	  _right(right),
	  _bottom(bottom)
{
}

int widget::Padding::Left() const
{
	return _left;
}

int widget::Padding::Top() const
{
	return _top;
}

int widget::Padding::Right() const
{
	return _right;
}

int widget::Padding::Bottom() const
{
	return _bottom;
}
