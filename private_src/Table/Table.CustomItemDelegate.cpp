#include "Table.CustomItemDelegate.h"

widget::Table::CustomItemDelegate::CustomItemDelegate(int padding)
	: _padding(padding)
{
}

void widget::Table::CustomItemDelegate::paint(QPainter *painter,
											  QStyleOptionViewItem const &option,
											  QModelIndex const &index) const
{
	// 创建一个新的 QStyleOptionViewItem 并初始化
	QStyleOptionViewItem new_option = option;
	initStyleOption(&new_option, index);

	QString text = index.data(Qt::DisplayRole).toString();

	QTextOption text_option{};
	text_option.setAlignment(Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);
	text_option.setWrapMode(QTextOption::WrapMode::NoWrap);

	QRect text_rect = new_option.rect;
	text_rect.adjust(_padding.Left(), _padding.Top(), -_padding.Right(), -_padding.Bottom());

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

QSize widget::Table::CustomItemDelegate::sizeHint(QStyleOptionViewItem const &option, QModelIndex const &index) const
{
	QSize size = QStyledItemDelegate::sizeHint(option, index);

	// 获取文本宽度并加上左右内边距
	QFontMetrics fm(option.font);
	QString text = index.data(Qt::DisplayRole).toString();
	int textWidth = fm.horizontalAdvance(text) + _padding.Left() + _padding.Right();
	size.setWidth(qMax(size.width(), textWidth));
	return size;
}
