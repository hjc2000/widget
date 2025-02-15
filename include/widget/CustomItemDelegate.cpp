#include "CustomItemDelegate.h"
#include <QPainter>

void widget::CustomItemDelegate::paint(QPainter *painter,
									   QStyleOptionViewItem const &option,
									   QModelIndex const &index) const
{
	// 创建一个新的 QStyleOptionViewItem 并初始化
	QStyleOptionViewItem new_option = option;
	initStyleOption(&new_option, index);

	// 修改 Highlight 和 HighlightedText 颜色
	QPalette new_palette = new_option.palette;

	// 设置选中时的背景颜色
	new_palette.setColor(QPalette::ColorGroup::Active,
						 QPalette::ColorRole::Highlight,
						 QColor{204, 232, 255});

	new_palette.setColor(QPalette::ColorGroup::Inactive,
						 QPalette::ColorRole::Highlight,
						 Qt::GlobalColor::white);

	// 设置选中时的文字颜色
	new_palette.setColor(QPalette::ColorGroup::Active,
						 QPalette::ColorRole::HighlightedText,
						 Qt::GlobalColor::black);

	new_palette.setColor(QPalette::ColorGroup::Inactive,
						 QPalette::ColorRole::HighlightedText,
						 Qt::GlobalColor::black);

	// 应用修改后的 palette
	new_option.palette = new_palette;

	// 调用基类绘制方法
	QStyledItemDelegate::paint(painter, new_option, index);
}
