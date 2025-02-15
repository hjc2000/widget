#pragma once
#include <base/delegate/Delegate.h>
#include <QTableView>

namespace widget
{
	class Table :
		public QTableView
	{
	private:
		base::Delegate<> _show_event;

		virtual bool event(QEvent *event) override;

	public:
		Table(QWidget *parent);

		/// @brief
		/// @param model 需要是一个堆上的对象。
		virtual void setModel(QAbstractItemModel *model) override;
	};
} // namespace widget
