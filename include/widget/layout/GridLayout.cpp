#include "GridLayout.h"
#include "Padding.h"
#include "qgridlayout.h"
#include "qnamespace.h"
#include "qwidget.h"
#include <base/string/define.h>
#include <stdexcept>

widget::GridLayout::GridLayout(QWidget *parent)
{
	_grid_layout = std::shared_ptr<QGridLayout>{new QGridLayout{parent}};
	_grid_layout->setSpacing(10);
	SetPadding(widget::Padding{0});
}

widget::GridLayout::GridLayout(QWidget *parent, widget::Padding const &padding)
	: GridLayout(parent)
{
	SetPadding(padding);
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

void widget::GridLayout::RemoveWidget(QWidget *widget)
{
	if (widget == nullptr)
	{
		return;
	}

	_grid_layout->removeWidget(widget);
}

void widget::GridLayout::RemoveWidget(int row, int column)
{
	QWidget *widget = GetWidget(row, column);
	if (widget != nullptr)
	{
		RemoveWidget(widget);
	}
}

QWidget *widget::GridLayout::GetWidget(int row, int column) const
{
	QLayoutItem *item = _grid_layout->itemAtPosition(row, column);
	return item->widget();
}

widget::GridPosition widget::GridLayout::GetWidgetPosition(QWidget *widget)
{
	for (int i = 0; i < _grid_layout->count(); i++)
	{
		QLayoutItem *item = _grid_layout->itemAt(i);
		if (item->widget() == widget)
		{
			int row = 0;
			int column = 0;
			int row_span = 1;
			int column_span = 1;

			_grid_layout->getItemPosition(i,
										  &row, &column,
										  &row_span, &column_span);

			return widget::GridPosition{row, column, row_span, column_span};
		}
	}

	throw std::runtime_error{CODE_POS_STR + "找不到该控件。"};
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

Qt::AlignmentFlag widget::GridLayout::Alignment() const
{
	return static_cast<Qt::AlignmentFlag>(_grid_layout->alignment().toInt());
}

void widget::GridLayout::SetAlignment(Qt::AlignmentFlag alignment)
{
	_grid_layout->setAlignment(alignment);
}

widget::Padding widget::GridLayout::Padding() const
{
	QMargins qmargin = _grid_layout->contentsMargins();

	return widget::Padding{
		qmargin.left(),
		qmargin.top(),
		qmargin.right(),
		qmargin.bottom(),
	};
}

void widget::GridLayout::SetPadding(widget::Padding const &value)
{
	_grid_layout->setContentsMargins(value.Left(), value.Top(),
									 value.Right(), value.Bottom());
}
