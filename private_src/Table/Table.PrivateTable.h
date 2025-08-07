#pragma once
#include "base/delegate/Delegate.h"
#include "base/delegate/IEvent.h"
#include "base/IDisposable.h"
#include "qevent.h"
#include "qtableview.h"
#include "widget/layout/Padding.h"
#include "widget/table/Table.h"
#include <vector>

///
/// @brief 私有的表格。派生 QTableView 以支持一些自定义特性，然后隐藏起来，作为私有代码，
/// 被公共的 Table 类以组合的方式进行包装。
///
///
class widget::Table::PrivateTable final :
	public QTableView,
	public base::IDisposable
{
private:
	bool _disposed = false;
	std::shared_ptr<CustomItemDelegate> _custom_item_delegate;
	QAbstractItemModel *_data_model = nullptr;

	base::Delegate<base::Position<int32_t> const &> _double_click_event;
	base::Delegate<widget::CurrentChangeEventArgs const &> _current_change_event;
	base::Delegate<QWheelEvent const &> _wheel_event;
	base::Delegate<int> _vertical_scroll_bar_value_change_event;

	std::vector<QMetaObject::Connection> _connections;

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

	virtual void currentChanged(QModelIndex const &current, QModelIndex const &previous) override
	{
		QTableView::currentChanged(current, previous);

		widget::CurrentChangeEventArgs args{current, previous};
		_current_change_event(args);
	}

	virtual void wheelEvent(QWheelEvent *event) override
	{
		// 调用基类处理滚动
		QTableView::wheelEvent(event);
		_wheel_event.Invoke(*event);
	}

public:
	///
	/// @brief 构造函数。
	///
	///
	PrivateTable();

	~PrivateTable()
	{
		Dispose();
	}

	///
	/// @brief 处置对象，让对象准备好结束生命周期。类似于进入 “准备后事” 的状态。
	///
	/// @note 注意，对象并不是析构了，并不是完全无法访问，它仍然允许访问，仍然能执行一些
	/// 符合 “准备后事” 的工作。
	///
	virtual void Dispose() override
	{
		if (_disposed)
		{
			return;
		}

		_disposed = true;

		_double_click_event.Dispose();
		_current_change_event.Dispose();
		_wheel_event.Dispose();
		_vertical_scroll_bar_value_change_event.Dispose();

		for (QMetaObject::Connection const &connection : _connections)
		{
			disconnect(connection);
		}
	}

	///
	/// @brief 设置数据模型。
	///
	/// @note 设置后需要手动调用 DataModelHasChanged 方法表格才会更新。
	///
	/// @param model
	///
	virtual void setModel(QAbstractItemModel *model) override;

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

	widget::Table::CustomItemDelegate &CustomItemDelegate()
	{
		return *_custom_item_delegate;
	}

	///
	/// @brief 第一个可见行的行索引。
	///
	/// @return
	///
	int FirstVisibleRowIndex() const
	{
		return rowAt(0);
	}

	/* #region 事件 */

	///
	/// @brief 单元格被双击事件。
	///
	/// @note 事件参数为 (base::Position const &position)
	///
	/// @return
	///
	base::IEvent<base::Position<int32_t> const &> &DoubleClickEvent()
	{
		return _double_click_event;
	}

	///
	/// @brief 当前焦点单元格发生改变的事件。
	///
	/// @return
	///
	base::IEvent<widget::CurrentChangeEventArgs const &> &CurrentChangeEvent()
	{
		return _current_change_event;
	}

	base::IEvent<QWheelEvent const &> &WheelEvent()
	{
		return _wheel_event;
	}

	base::IEvent<int> &VerticalScrollBarValueChangeEvent()
	{
		return _vertical_scroll_bar_value_change_event;
	}

	/* #endregion */
};
