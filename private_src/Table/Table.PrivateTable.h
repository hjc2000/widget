#pragma once
#include "base/delegate/IEvent.h"
#include "qtableview.h"
#include "widget/layout/Padding.h"
#include "widget/table/Table.h"

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

	base::Delegate<base::Position const &> _double_click_event;
	base::Delegate<QModelIndex const &, QModelIndex const &> _current_change_event;

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

	void currentChanged(QModelIndex const &current, QModelIndex const &previous) override
	{
		QTableView::currentChanged(current, previous);
		_current_change_event(current, previous);
	}

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
	void SetColumnResizeModes(std::vector<QHeaderView::ResizeMode> resize_modes);

	///
	/// @brief 单元格的边距。
	///
	/// @return
	///
	widget::Padding ItemPadding() const;

	///
	/// @brief 设置单元格的边距。
	///
	/// @param value
	///
	void SetItemPadding(widget::Padding const &value);

	/* #region 事件 */

	///
	/// @brief 单元格被双击事件。
	///
	/// @note 事件参数为 (base::Position const &position)
	///
	/// @return base::IEvent<base::Position const &>&
	///
	base::IEvent<base::Position const &> &DoubleClickEvent()
	{
		return _double_click_event;
	}

	///
	/// @brief 当前焦点单元格发生改变的事件。
	///
	/// @note 事件参数为 (QModelIndex const &current, QModelIndex const &previous)
	///
	/// @return
	///
	base::IEvent<QModelIndex const &, QModelIndex const &> &CurrentChangeEvent()
	{
		return _current_change_event;
	}

	/* #endregion */
};
