#pragma once
#include "widget/table/Table.h"
#include <cstdint>

///
/// @brief 私有的表格。派生 QTableView 以支持一些自定义特性，然后隐藏起来，作为私有代码，
/// 被公共的 Table 类以组合的方式进行包装。
///
///
class widget::Table::PrivateTable :
	public QTableView
{
private:
	std::shared_ptr<CustomItemDelegate> _custom_item_delegate;
	QAbstractItemModel *_data_model = nullptr;

	///
	/// @brief 单元格被双击事件。
	///
	///
	base::Delegate<base::Position const &> _double_click_event;

	void ConnectSignals();

	///
	/// @brief 避免在启动后表格第一时间就已经聚焦到第一个单元格了。
	///
	///
	void ClearInitialFocus();

	///
	/// @brief 清除表头显示的排序箭头。
	///
	///
	void ClearSortIndicator();

public:
	///
	/// @brief 构造函数。
	///
	///
	PrivateTable();

	///
	/// @brief 设置数据模型。
	///
	/// @note 设置后需要手动调用 DataModelHasChanged 方法表格才会更新。
	///
	/// @param model
	///
	virtual void setModel(QAbstractItemModel *model) override;

	///
	/// @brief 设置每一列的大小调整方式。
	///
	/// @param resize_modes
	///
	void SetResizeModes(std::vector<QHeaderView::ResizeMode> resize_modes);

	int32_t ItemPadding() const;

	void SetItemPadding(int32_t value);

	/* #region 事件 */

	///
	/// @brief 单元格被双击事件。
	///
	/// @return base::IEvent<base::Position const &>&
	///
	base::IEvent<base::Position const &> &DoubleClickEvent();

	/* #endregion */
};
