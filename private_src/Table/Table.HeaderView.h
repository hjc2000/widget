#pragma once
#include "qcolor.h"
#include "qheaderview.h"
#include "widget/PainterGuard.h"
#include "widget/table/Table.h"

class widget::Table::HeaderView :
	public QHeaderView
{
private:
	int _selected_index = -1;

protected:
	void paintSection(QPainter *painter, QRect const &rect, int logicalIndex) const override
	{
		widget::PainterGuard g{painter};

		// 设置内边距（左10px，右10px，上5px，下5px）
		QRect paddedRect = rect.adjusted(10, 5, -10, -5);

		// 绘制背景（可选）
		painter->fillRect(rect, QColor{240, 240, 240});

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

			painter->drawText(paddedRect, Qt::AlignmentFlag::AlignLeft, text);
		}
	}

	QSize sizeHint() const override
	{
		QSize size = QHeaderView::sizeHint();
		size.setWidth(size.width() + 20);   // 左右各增加10px
		size.setHeight(size.height() + 10); // 上下各增加5px
		return size;
	}

public:
	HeaderView(Qt::Orientation orientation)
		: QHeaderView(orientation, nullptr)
	{
		setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
	}

	void SetSelectedIndex(int index)
	{
		_selected_index = index;
	}
};
