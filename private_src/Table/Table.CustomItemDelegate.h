#pragma once
#include "qnamespace.h"
#include "widget/layout/Padding.h"
#include "widget/table/Table.h"
#include <cstdint>
#include <iostream>
#include <vector>

///
/// @brief 按照自定义的方式绘制单元格。
///
///
class widget::Table::CustomItemDelegate :
	public QStyledItemDelegate
{
private:
	widget::Padding _padding{10, 5, 10, 5};
	std::vector<Qt::AlignmentFlag> _alignments;

	Qt::AlignmentFlag _default_alignment = static_cast<Qt::AlignmentFlag>(static_cast<uint32_t>(Qt::AlignmentFlag::AlignLeft) |
																		  static_cast<uint32_t>(Qt::AlignmentFlag::AlignVCenter));

public:
	CustomItemDelegate() = default;

	~CustomItemDelegate()
	{
		std::cout << __func__ << std::endl;
	}

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

	///
	/// @brief 设置各个列的对齐方式。
	///
	/// @param alignments
	///
	void SetColumnAlignments(std::vector<Qt::AlignmentFlag> const &alignments)
	{
		_alignments = alignments;
	}
};
