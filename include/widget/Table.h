#pragma once
#include <QTableView>

namespace widget
{
	class Table :
		public QTableView
	{
	public:
		Table(QWidget *parent);

		virtual void setModel(QAbstractItemModel *model) override;
	};
} // namespace widget
