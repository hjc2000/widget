#include "FormTableLayout.h"
#include "qnamespace.h"

void widget::FormTableLayout::Initialize()
{
	_grid_layout->SetColumnStretch(1, 1);
	_grid_layout->SetAlignment(Qt::AlignmentFlag::AlignTop);
}

widget::FormTableLayout::FormTableLayout(QWidget *parent)
{
	_grid_layout = std::shared_ptr<widget::GridLayout>{new widget::GridLayout{parent}};
	Initialize();
}

widget::FormTableLayout::FormTableLayout(QWidget *parent, widget::Padding const &padding)
{
	_grid_layout = std::shared_ptr<widget::GridLayout>{new widget::GridLayout{parent, padding}};
	Initialize();
}

void widget::FormTableLayout::SetItem(int row, QWidget *left, QWidget *right)
{
	_grid_layout->AddWidget(left, row, 0, Qt::AlignmentFlag::AlignTop);
	_grid_layout->AddWidget(right, row, 1, Qt::AlignmentFlag::AlignTop);
}

void widget::FormTableLayout::RemoveItem(int row)
{
	_grid_layout->RemoveWidget(row, 0);
	_grid_layout->RemoveWidget(row, 1);
}

widget::Padding widget::FormTableLayout::Padding() const
{
	return _grid_layout->Padding();
}

void widget::FormTableLayout::SetPadding(widget::Padding const &value)
{
	_grid_layout->SetPadding(value);
}
