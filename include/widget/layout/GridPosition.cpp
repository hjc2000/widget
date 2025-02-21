#include "GridPosition.h"

widget::GridPosition::GridPosition(int row, int column, int row_span, int column_span)
{
	_row = row;
	_column = column;
	_row_span = row_span;
	_column_span = column_span;
}

int widget::GridPosition::Row() const
{
	return _row;
}

int widget::GridPosition::Column() const
{
	return _column;
}

int widget::GridPosition::RowSpan() const
{
	return _row_span;
}

int widget::GridPosition::ColumnSpan() const
{
	return _column_span;
}
