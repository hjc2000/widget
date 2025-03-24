#include "Table.PrivateTable.h"
#include <Table.CustomItemDelegate.h>
#include <widget/Conversion.h>
#include <widget/line-input-widget/Submit.h>

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
		_custom_item_delegate = std::shared_ptr<CustomItemDelegate>{new CustomItemDelegate{}};
		setItemDelegate(_custom_item_delegate.get());
	}
}

void widget::Table::PrivateTable::setModel(QAbstractItemModel *model)
{
	_data_model = model;
}

void widget::Table::PrivateTable::DataModelHasChanged()
{
	if (_data_model == nullptr)
	{
		return;
	}

	/* 先设置成空指针，避免以前已经有模型了。
	 * 如果以前已经有模型了，不先设置成空指针清空模型，就会出现表格视图没有刷新完全的情况。例如行数
	 * 还保持着上一个模型的行数。
	 */
	QTableView::setModel(nullptr);
	QTableView::setModel(_data_model);
	ClearInitialFocus();

	{
		QHeaderView *header = horizontalHeader();
		header->setSectionResizeMode(QHeaderView::Interactive);

		for (int i = 0; i < _data_model->columnCount(); i++)
		{
			resizeColumnToContents(i);
		}
	}

	{
		QHeaderView *header = horizontalHeader();

		// 允许用户移动列
		header->setSectionsMovable(true);

		// 允许用户点击列头
		header->setSectionsClickable(true);
	}

	// 添加、删除数据或者数据被编辑后表格实际上可能变成乱序了，所以需要清除排序箭头。
	ClearSortIndicator();
}

void widget::Table::PrivateTable::SetResizeModes(std::vector<QHeaderView::ResizeMode> resize_modes)
{
	QHeaderView *header = horizontalHeader();
	int count = std::min(header->count(), static_cast<int>(resize_modes.size()));
	for (int i = 0; i < count; ++i)
	{
		header->setSectionResizeMode(i, resize_modes[i]);
	}
}
