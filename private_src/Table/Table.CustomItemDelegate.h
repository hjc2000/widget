#pragma once
#include "widget/table/Table.h"
#include <cstdint>

///
/// @brief 按照自定义的方式绘制单元格。
///
///
class widget::Table::CustomItemDelegate :
	public QStyledItemDelegate
{
private:
	int32_t _padding = 10;

public:
	CustomItemDelegate() = default;

	CustomItemDelegate(int padding);

	///
	/// @brief 绘制单元格。
	///
	/// @param painter
	/// @param option
	/// @param index
	///
	void paint(QPainter *painter,
			   QStyleOptionViewItem const &option,
			   QModelIndex const &index) const override;

	///
	/// @brief qt 框架会调用本函数来获取单元格应该被设置成的大小。
	///
	/// @param option
	/// @param index
	/// @return QSize
	///
	QSize sizeHint(QStyleOptionViewItem const &option, QModelIndex const &index) const override;

	int32_t Padding() const
	{
		return _padding;
	}

	void SetPadding(int32_t value)
	{
		_padding = value;
	}
};
