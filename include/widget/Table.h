#pragma once
#include <QHeaderView>
#include <QTableView>
#include <vector>

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

		/// @brief 设置数据模型，同时设置每一列的大小调整方式。
		/// @param model
		/// @param resize_modes
		void setModel(QAbstractItemModel *model, std::vector<QHeaderView::ResizeMode> resize_modes);
	};
} // namespace widget
