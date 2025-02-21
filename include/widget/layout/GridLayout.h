#pragma once
#include <memory>
#include <qgridlayout.h>
#include <qwidget.h>

namespace widget
{
	class GridLayout
	{
	private:
		std::shared_ptr<QGridLayout> _grid_layout{};

	public:
		GridLayout(QWidget *parent);

	public:
		void AddWidget(QWidget *widget, int row, int column);
		void AddWidget(QWidget *widget, int row, int column, int row_span, int column_span);

	public:
		int RowStretch(int row) const;
		void SetRowStretch(int row, int stretch);

		int ColumnStretch(int column) const;
		void SetColumnStretch(int column, int stretch);
	};
} // namespace widget
