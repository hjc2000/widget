#pragma once
#include "qheaderview.h"
#include "widget/table/Table.h"

class widget::Table::HeaderView :
	public QHeaderView
{
private:
	int _selected_index = -1;

protected:
	void paintSection(QPainter *painter, QRect const &rect, int logicalIndex) const override
	{
		// 设置内边距（左10px，右10px，上5px，下5px）
		QRect paddedRect = rect.adjusted(10, 5, -10, -5);

		// 绘制背景（可选）
		painter->fillRect(rect, QColor{240, 240, 240});

		// 绘制文本（居中）
		QString text = model()->headerData(logicalIndex, orientation()).toString();

		if (logicalIndex == _selected_index)
		{
			QFont font = painter->font();
			font.setBold(true);
			painter->setFont(font);
		}

		painter->drawText(paddedRect, Qt::AlignmentFlag::AlignLeft, text);
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
