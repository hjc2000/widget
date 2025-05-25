#pragma once
#include "widget/layout/Padding.h"
#include "widget/table/Table.h"

///
/// @brief 按照自定义的方式绘制单元格。
///
///
class widget::Table::CustomItemDelegate :
	public QStyledItemDelegate
{
private:
	widget::Padding _padding{10, 0, 10, 0};

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

	widget::Padding Padding() const
	{
		return _padding;
	}

	void SetPadding(widget::Padding const value)
	{
		_padding = value;
	}
};
