#include "Table.HeaderView.h" // IWYU pragma: keep
#include "qcolor.h"
#include "widget/PainterGuard.h"

void widget::Table::HeaderView::paintSection(QPainter *painter,
											 QRect const &rect,
											 int logicalIndex) const
{
	widget::PainterGuard g{painter};

	// 设置内边距（左10px，右10px，上5px，下5px）
	QRect paddedRect = rect.adjusted(_padding.Left(),
									 _padding.Top(),
									 -_padding.Right(),
									 -_padding.Bottom());

	// 绘制背景（可选）
	painter->fillRect(rect, QColor{245, 245, 245});

	{
		// 绘制边框
		widget::PainterGuard g{painter};
		QRectF border_rect{rect};
		border_rect.adjust(-0.5, -0.5, -0.5, -0.5);
		QPen pen(Qt::GlobalColor::gray);
		pen.setWidth(1);
		pen.setColor(QColor{185, 185, 185});
		painter->setPen(pen);
		painter->drawRect(border_rect);
	}

	{
		// 绘制文本
		widget::PainterGuard g{painter};
		QString text = model()->headerData(logicalIndex, orientation()).toString();

		if (logicalIndex == _selected_index)
		{
			QFont font = painter->font();
			font.setBold(true);
			painter->setFont(font);
		}

		painter->drawText(paddedRect, _text_alignment, text);
	}
}

QSize widget::Table::HeaderView::sizeHint() const
{
	QSize size = QHeaderView::sizeHint();
	size.setWidth(size.width() + _padding.Left() + _padding.Right());
	size.setHeight(size.height() + _padding.Top() + _padding.Bottom());
	return size;
}
