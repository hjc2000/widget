#pragma once
#include "qheaderview.h"
#include "qnamespace.h"
#include "widget/layout/Padding.h"
#include "widget/table/Table.h"
#include <cstdint>

class widget::Table::HeaderView :
	public QHeaderView
{
private:
	int _selected_index = -1;
	Qt::AlignmentFlag _text_alignment = static_cast<Qt::AlignmentFlag>(static_cast<uint32_t>(Qt::AlignmentFlag::AlignLeft) | static_cast<uint32_t>(Qt::AlignmentFlag::AlignVCenter));
	widget::Padding _padding{10, 5, 10, 5};

protected:
	void paintSection(QPainter *painter, QRect const &rect, int logicalIndex) const override;

	QSize sizeHint() const override;

public:
	HeaderView(Qt::Orientation orientation)
		: QHeaderView(orientation, nullptr)
	{
		setSectionResizeMode(QHeaderView::ResizeMode::Fixed);

		if (orientation == Qt::Orientation::Vertical)
		{
			// 派生 QHeaderView 类，自定义绘制后，行标题老是不够高，所以就在这里设置默认
			// 的 Section 尺寸，对于行标题来说就是高度。让高度比默认值增加 10.
			//
			// 对于列标题来说，Section 大小控制的是宽度。
			setDefaultSectionSize(defaultSectionSize() + 10);
		}
	}

	void SetSelectedIndex(int index)
	{
		_selected_index = index;
	}

	widget::Padding Padding() const
	{
		return _padding;
	}

	void SetPadding(widget::Padding const &value)
	{
		_padding = value;
	}

	Qt::AlignmentFlag TextAlignment() const
	{
		return _text_alignment;
	}

	void SetTextAlignment(Qt::AlignmentFlag value)
	{
		_text_alignment = value;
	}
};
