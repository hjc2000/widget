#include "Table.h"
#include <base/string/Parse.h>
#include <QAbstractTableModel>
#include <QHeaderView>
#include <QPainter>
#include <QStyledItemDelegate>
#include <string>
#include <widget/Conversion.h>
#include <widget/InputWidget.h>

widget::Table::Table(QWidget *parent)
	: QTableView(parent)
{
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
