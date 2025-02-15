#pragma once
#include <QTableView>

namespace widget
{
	class Table :
		public QTableView
	{
	private:
		virtual void enterEvent(QEnterEvent *event) override;
		virtual void leaveEvent(QEvent *event) override;

	public:
		Table(QWidget *parent);

		/// @brief
		/// @param model 需要是一个堆上的对象。
		virtual void setModel(QAbstractItemModel *model) override;
	};
} // namespace widget
