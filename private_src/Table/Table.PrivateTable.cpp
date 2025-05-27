#include "Table.PrivateTable.h"
#include "base/math/Position.h"
#include <Table.CustomItemDelegate.h>
#include <widget/convert.h>
#include <widget/line-input-widget/Submit.h>

void widget::Table::PrivateTable::ConnectSignals()
{
	connect(this,
			&widget::Table::PrivateTable::doubleClicked,
			[this](QModelIndex const &index)
			{
				_double_click_event.Invoke(base::Position{index.column(), index.row()});
			});
}

void widget::Table::PrivateTable::ClearInitialFocus()
{
	clearFocus();
	setCurrentIndex(QModelIndex{});
}

void widget::Table::PrivateTable::ClearSortIndicator()
{
	QHeaderView *header = horizontalHeader();
	if (header == nullptr)
	{
		return;
	}

	header->setSortIndicator(-1, Qt::SortOrder::DescendingOrder);
}

widget::Table::PrivateTable::PrivateTable()
{
	ConnectSignals();
	setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);

	{
		// 设置选择行为为选择单元格
		setSelectionBehavior(SelectionBehavior::SelectRows);
		setSelectionMode(SelectionMode::SingleSelection);
	}

	{
		// 设置滚动方式为逐个像素滚动。
		setHorizontalScrollMode(ScrollMode::ScrollPerPixel);
		setVerticalScrollMode(ScrollMode::ScrollPerPixel);
	}

	{
		// 设置单元格绘制代理，按照自定义的方式绘制单元格。
		_custom_item_delegate = std::shared_ptr<widget::Table::CustomItemDelegate>{new widget::Table::CustomItemDelegate{}};
		setItemDelegate(_custom_item_delegate.get());
	}
}

void widget::Table::PrivateTable::setModel(QAbstractItemModel *model)
{
	_data_model = model;

	// 先设置成空指针，避免以前已经有模型了。
	// 如果以前已经有模型了，不先设置成空指针清空模型，就会出现表格视图没有刷新完全的情况。例如行数
	// 还保持着上一个模型的行数。
	QTableView::setModel(nullptr);
	QTableView::setModel(_data_model);

	if (_data_model == nullptr)
	{
		return;
	}

	ClearInitialFocus();

	// 添加、删除数据或者数据被编辑后表格实际上可能变成乱序了，所以需要清除排序箭头。
	ClearSortIndicator();
}

widget::Padding widget::Table::PrivateTable::ItemPadding() const
{
	return _custom_item_delegate->Padding();
}

void widget::Table::PrivateTable::SetItemPadding(widget::Padding const &value)
{
	_custom_item_delegate->SetPadding(value);

	// 放心地在样式设置函数中调用 update, 因为同一个事件循环周期中，多个
	// update 调用会合并成一个。
	update();
}
