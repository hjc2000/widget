#pragma once
#include <memory>
#include <QHeaderView>
#include <QTableView>
#include <widget/table/Table.h>

/**
 * @brief 表格。
 *
 */
class widget::Table::PrivateTable :
	public QTableView
{
private:
	std::shared_ptr<CustomItemDelegate> _custom_item_delegate;
	QAbstractItemModel *_data_model = nullptr;

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
	PrivateTable();

public:
	// 数据模型

	/**
	 * @brief 设置数据模型。
	 *
	 * @param model 需要是一个堆上的对象。
	 */
	virtual void setModel(QAbstractItemModel *model) override;

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
