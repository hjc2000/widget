#pragma once
#include "qheaderview.h"
#include "widget/table/Table.h"

class widget::Table::HeaderView :
	public QHeaderView
{
private:
	int _selected_index = -1;

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
