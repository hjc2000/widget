#pragma once
#include <memory>
#include <QHeaderView>
#include <QTableView>
#include <qwidget.h>
#include <widget/layout/HBoxLayout.h>

namespace widget
{
	/**
	 * @brief 表格。
	 *
	 */
	class Table :
		public QWidget
	{
	private:
		class PrivateTable;
		class CustomItemDelegate;

		std::shared_ptr<PrivateTable> _table;
		widget::HBoxLayout _layout{this};

	public:
		/**
		 * @brief Construct a new Table object
		 *
		 */
		Table();

	public:
		// 数据模型

		/**
		 * @brief 设置数据模型。
		 *
		 * @param model 需要是一个堆上的对象。
		 */
		void SetModel(QAbstractItemModel *model);

		/**
		 * @brief 设置数据模型，同时设置每一列的大小调整方式。
		 *
		 * @param model
		 * @param resize_modes
		 */
		void SetModel(QAbstractItemModel *model, std::vector<QHeaderView::ResizeMode> resize_modes);

		/**
		 * @brief 数据模型发生改变，需要刷新表格视图。
		 *
		 */
		void DataModelHasChanged();

	public:
		/**
		 * @brief 设置每一列的大小调整方式。
		 *
		 * @param resize_modes
		 */
		void SetResizeModes(std::vector<QHeaderView::ResizeMode> resize_modes);
	};
} // namespace widget
