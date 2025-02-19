#include "Table.h"
#include <base/string/Parse.h>
#include <QAbstractTableModel>
#include <QApplication>
#include <QPainter>
#include <QStyledItemDelegate>
#include <widget/Conversion.h>
#include <widget/line-input-widget/Submit.h>

/// @brief 按照自定义的方式绘制单元格。
class widget::Table::CustomItemDelegate :
	public QStyledItemDelegate
{
private:
	int _padding = 10;

public:
	void paint(QPainter *painter,
			   QStyleOptionViewItem const &option,
			   QModelIndex const &index) const override
	{
		// 创建一个新的 QStyleOptionViewItem 并初始化
		QStyleOptionViewItem new_option = option;
		initStyleOption(&new_option, index);

		QString text = index.data(Qt::DisplayRole).toString();

		QTextOption text_option{};

		text_option.setAlignment(Qt::AlignmentFlag::AlignLeft |
								 Qt::AlignmentFlag::AlignVCenter);

		QRect text_rect = new_option.rect;
		text_rect.adjust(_padding, 0, -_padding, 0);

		if (new_option.state & QStyle::State_Selected)
		{
			if (new_option.state & QStyle::State_Active)
			{
				painter->fillRect(new_option.rect, QColor{204, 232, 255});
				painter->drawText(text_rect, text, text_option);
			}
			else
			{
				painter->fillRect(new_option.rect, QColor{240, 240, 240});
				painter->drawText(text_rect, text, text_option);
			}
		}
		else
		{
			painter->fillRect(new_option.rect, Qt::GlobalColor::white);
			painter->drawText(text_rect, text, text_option);
		}
	}

	QSize sizeHint(QStyleOptionViewItem const &option, QModelIndex const &index) const override
	{
		QSize size = QStyledItemDelegate::sizeHint(option, index);

		// 获取文本宽度并加上左右内边距
		QFontMetrics fm(option.font);
		QString text = index.data(Qt::DisplayRole).toString();
		int textWidth = fm.horizontalAdvance(text) + 2 * _padding;
		size.setWidth(qMax(size.width(), textWidth));
		return size;
	}
};

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

void widget::Table::SetAsPerPixelScroll()
{
	setHorizontalScrollMode(ScrollMode::ScrollPerPixel);
	setVerticalScrollMode(ScrollMode::ScrollPerPixel);
}

widget::Table::Table()
{
	_custom_item_delegate = std::shared_ptr<CustomItemDelegate>{new CustomItemDelegate{}};

	setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);

	{
		// 设置选择行为为选择单元格
		setSelectionBehavior(SelectionBehavior::SelectItems);
		setSelectionMode(SelectionMode::SingleSelection);
	}

	SetAsPerPixelScroll();

	// 设置单元格绘制代理，按照自定义的方式绘制单元格。
	setItemDelegate(_custom_item_delegate.get());
}

void widget::Table::setModel(QAbstractItemModel *model)
{
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
