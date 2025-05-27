#pragma once
#include "qheaderview.h"
#include "widget/layout/Padding.h"
#include "widget/table/Table.h"

class widget::Table::HeaderView :
	public QHeaderView
{
private:
	int _selected_index = -1;
	widget::Padding _padding{10, 5, 10, 5};

protected:
	void paintSection(QPainter *painter, QRect const &rect, int logicalIndex) const override;

	QSize sizeHint() const override;

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
