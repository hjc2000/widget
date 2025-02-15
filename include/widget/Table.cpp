#include "Table.h"
#include <base/string/Parse.h>
#include <QAbstractTableModel>
#include <QHeaderView>
#include <QPainter>
#include <QStyledItemDelegate>
#include <string>
#include <widget/Conversion.h>
#include <widget/InputWidget.h>

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

widget::Table::Table(QWidget *parent)
	: QTableView(parent)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void widget::Table::setModel(QAbstractItemModel *model)
{
	QTableView::setModel(model);

	{
		// 避免在启动后表格第一时间就已经聚焦到第一个单元格了。
		clearFocus();
		setCurrentIndex(QModelIndex{});
	}

	{
		// 设置列头可手动调整
		QHeaderView *header = horizontalHeader();
		header->setSectionResizeMode(QHeaderView::Interactive);
		header->setSectionResizeMode(1, QHeaderView::Stretch);
		header->setSectionsMovable(true);   // 允许用户移动列
		header->setSectionsClickable(true); // 允许用户点击列头
	}
}
