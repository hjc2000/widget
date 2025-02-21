#include "FormTableLayout.h"
#include "qlabel.h"
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

void widget::FormTableLayout::SetItem(int row, std::string const &label, QWidget *widget)
{
	std::shared_ptr<QLabel> qlabel{new QLabel{label.c_str()}};
	qlabel->setSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);

	_label_dic.Set(row, qlabel);
	_grid_layout->AddWidget(qlabel.get(), row, 0, Qt::AlignmentFlag::AlignTop);
	_grid_layout->AddWidget(widget, row, 1, Qt::AlignmentFlag::AlignTop);
}

void widget::FormTableLayout::RemoveItem(int row)
{
	_label_dic.Remove(row);
	_grid_layout->RemoveWidget(row, 0);
	_grid_layout->RemoveWidget(row, 1);
}
