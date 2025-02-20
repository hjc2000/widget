#include "Table.h"
#include <base/string/Parse.h>
#include <CustomItemDelegate.h>
#include <QAbstractTableModel>
#include <QApplication>
#include <QPainter>
#include <QStyledItemDelegate>
#include <widget/Conversion.h>
#include <widget/line-input-widget/Submit.h>

void widget::Table::enterEvent(QEnterEvent *event)
{
	QTableView::enterEvent(event);

	static bool first_time = true;
	if (first_time)
	{
		first_time = false;
		QHeaderView *header = horizontalHeader();
		header->setSectionResizeMode(QHeaderView::Interactive);
	}
}

void widget::Table::leaveEvent(QEvent *event)
{
	QTableView::leaveEvent(event);
}

void widget::Table::ClearInitialFocus()
{
	clearFocus();
	setCurrentIndex(QModelIndex{});
}

widget::Table::Table()
{
	_custom_item_delegate = std::shared_ptr<CustomItemDelegate>{new CustomItemDelegate{}};

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

	// 设置单元格绘制代理，按照自定义的方式绘制单元格。
	setItemDelegate(_custom_item_delegate.get());

	// 使能排序
	setSortingEnabled(true);
}

void widget::Table::setModel(QAbstractItemModel *model)
{
	/* 先设置成空指针，避免以前已经有模型了。
	 * 如果以前已经有模型了，不先设置成空指针清空模型，就会出现表格视图没有刷新完全的情况。例如行数
	 * 还保持着上一个模型的行数。
	 */
	QTableView::setModel(nullptr);
	QTableView::setModel(model);
	ClearInitialFocus();

	{
		// 设置列头自适应大小。
		QHeaderView *header = horizontalHeader();
		header->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
	}

	{
		QHeaderView *header = horizontalHeader();

		// 允许用户移动列
		header->setSectionsMovable(true);

		// 允许用户点击列头
		header->setSectionsClickable(true);
	}
}

void widget::Table::setModel(QAbstractItemModel *model,
							 std::vector<QHeaderView::ResizeMode> resize_modes)
{
	setModel(model);
	SetResizeModes(resize_modes);
}

void widget::Table::SetResizeModes(std::vector<QHeaderView::ResizeMode> resize_modes)
{
	QHeaderView *header = horizontalHeader();
	int count = std::min(header->count(), static_cast<int>(resize_modes.size()));
	for (int i = 0; i < count; ++i)
	{
		header->setSectionResizeMode(i, resize_modes[i]);
	}
}
