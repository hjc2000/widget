#include "FormTableLayout.h"

void widget::FormTableLayout::Initialize()
{
	// 第 0 列的增长因子为 0，不允许增长，而是根据内容调整大小。
	_grid_layout->SetColumnStretch(0, 0);

	// 增长因子为 1，凡是增长因子不为 0 的，都会根据因子的比例去分配剩余的宽度。
	// 这里一共 2 列，其中第 0 列增长因子为 0，所以第 1 列就占据所有剩余宽度。
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
	_grid_layout->AddWidget(left, row, 0);
	_grid_layout->AddWidget(right, row, 1);
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
