#include "Table.CustomItemDelegate.h"

void widget::Table::CustomItemDelegate::paint(QPainter *painter,
											  QStyleOptionViewItem const &option,
											  QModelIndex const &index) const
{
	// 创建一个新的 QStyleOptionViewItem 并初始化
	QStyleOptionViewItem new_option = option;
	initStyleOption(&new_option, index);

	QString text = index.data(Qt::DisplayRole).toString();

	QTextOption text_option{};
	if (index.column() >= static_cast<int>(_alignments.size()))
	{
		text_option.setAlignment(_default_alignment);
	}
	else
	{
		text_option.setAlignment(_alignments[index.column()]);
	}

	text_option.setWrapMode(QTextOption::WrapMode::NoWrap);

	QRect text_rect = new_option.rect;

	text_rect.adjust(_padding.Left(),
					 _padding.Top(),
					 -_padding.Right(),
					 -_padding.Bottom());

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
	size.setWidth(size.width() + _padding.Left() + _padding.Right());
	size.setHeight(size.height() + _padding.Top() + _padding.Bottom());
	return size;
}
