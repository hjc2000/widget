#include "GridLayout.h"
#include "qgridlayout.h"
#include "qnamespace.h"

widget::GridLayout::GridLayout(QWidget *parent)
{
	_grid_layout = std::shared_ptr<QGridLayout>{new QGridLayout{parent}};
	_grid_layout->setSpacing(10);
	_grid_layout->setContentsMargins(0, 0, 0, 0);
}

widget::GridLayout::GridLayout(QWidget *parent, widget::Padding const &padding)
	: GridLayout(parent)
{
	_grid_layout->setContentsMargins(padding.Left(), padding.Top(),
									 padding.Right(), padding.Bottom());
}

void widget::GridLayout::AddWidget(QWidget *widget, int row, int column)
{
	AddWidget(widget, row, column, 1, 1);
}

void widget::GridLayout::AddWidget(QWidget *widget, int row, int column, Qt::AlignmentFlag align)
{
	AddWidget(widget, row, column, 1, 1, align);
}

void widget::GridLayout::AddWidget(QWidget *widget, int row, int column, int row_span, int column_span)
{
	AddWidget(widget,
			  row,
			  column,
			  row_span,
			  column_span,
			  static_cast<Qt::AlignmentFlag>(0));
}

void widget::GridLayout::AddWidget(QWidget *widget,
								   int row,
								   int column,
								   int row_span,
								   int column_span,
								   Qt::AlignmentFlag align)
{
	_grid_layout->addWidget(widget,
							row,
							column,
							row_span,
							column_span,
							align);
}

int widget::GridLayout::RowStretch(int row) const
{
	return _grid_layout->rowStretch(row);
}

void widget::GridLayout::SetRowStretch(int row, int stretch)
{
	_grid_layout->setRowStretch(row, stretch);
}

int widget::GridLayout::ColumnStretch(int column) const
{
	return _grid_layout->columnStretch(column);
}

void widget::GridLayout::SetColumnStretch(int column, int stretch)
{
	_grid_layout->setColumnStretch(column, stretch);
}
