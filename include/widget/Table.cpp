#include "Table.h"
#include <base/string/Parse.h>
#include <QAbstractTableModel>
#include <QHeaderView>
#include <QPainter>
#include <QStyledItemDelegate>
#include <string>
#include <widget/Conversion.h>
#include <widget/InputWidget.h>

namespace
{
	class CustomItemDelegate :
		public QStyledItemDelegate
	{
	public:
		using QStyledItemDelegate::QStyledItemDelegate;

		void paint(QPainter *painter,
				   QStyleOptionViewItem const &option,
				   QModelIndex const &index) const override
		{
			// 创建一个新的 QStyleOptionViewItem 并初始化
			QStyleOptionViewItem new_option = option;
			initStyleOption(&new_option, index);

			// 修改 Highlight 和 HighlightedText 颜色
			QPalette new_palette = new_option.palette;

			// 单元格获得焦点时的背景颜色。
			new_palette.setColor(QPalette::ColorGroup::Active,
								 QPalette::ColorRole::Highlight,
								 QColor{204, 232, 255});

			// 单元格从拥有焦点变成失去焦点时的背景颜色。
			new_palette.setColor(QPalette::ColorGroup::Inactive,
								 QPalette::ColorRole::Highlight,
								 QColor{240, 240, 240});

			// 单元格获得焦点时的文字颜色。
			new_palette.setColor(QPalette::ColorGroup::Active,
								 QPalette::ColorRole::HighlightedText,
								 Qt::GlobalColor::black);

			// 单元格从拥有焦点变成失去焦点时的文字颜色。
			new_palette.setColor(QPalette::ColorGroup::Inactive,
								 QPalette::ColorRole::HighlightedText,
								 Qt::GlobalColor::black);

			// 应用修改后的 palette
			new_option.palette = new_palette;

			// 调用基类绘制方法
			QStyledItemDelegate::paint(painter, new_option, index);
		}
	};
} // namespace

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
	setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
	setSelectionBehavior(SelectionBehavior::SelectItems);
	setSelectionMode(SelectionMode::SingleSelection);

	setHorizontalScrollMode(ScrollMode::ScrollPerPixel);
	setVerticalScrollMode(ScrollMode::ScrollPerPixel);

	setItemDelegate(new CustomItemDelegate{this});
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
