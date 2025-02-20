#pragma once
#include <memory>
#include <QHeaderView>
#include <QTableView>
#include <vector>

namespace widget
{
	class CustomItemDelegate;

	/**
	 * @brief 表格。
	 *
	 */
	class Table :
		public QTableView
	{
	private:
		std::shared_ptr<CustomItemDelegate> _custom_item_delegate;

	private: // 事件
		virtual void enterEvent(QEnterEvent *event) override;
		virtual void leaveEvent(QEvent *event) override;

	private:
		/**
		 * @brief 避免在启动后表格第一时间就已经聚焦到第一个单元格了。
		 *
		 */
		void ClearInitialFocus();

	public:
		/**
		 * @brief Construct a new Table object
		 *
		 */
		Table();

	public: // 数据模型
		/**
		 * @brief 设置数据模型。
		 *
		 * @param model 需要是一个堆上的对象。
		 */
		virtual void setModel(QAbstractItemModel *model) override;

		/**
		 * @brief 设置数据模型，同时设置每一列的大小调整方式。
		 *
		 * @param model
		 * @param resize_modes
		 */
		void setModel(QAbstractItemModel *model, std::vector<QHeaderView::ResizeMode> resize_modes);

	public:
		/**
		 * @brief 设置每一列的大小调整方式。
		 *
		 * @param resize_modes
		 */
		void SetResizeModes(std::vector<QHeaderView::ResizeMode> resize_modes);
	};
} // namespace widget
