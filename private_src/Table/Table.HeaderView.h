#pragma once
#include "qheaderview.h"
#include "qnamespace.h"
#include "widget/AlignmentFlag.h"
#include "widget/layout/Padding.h"
#include "widget/table/Table.h"

class widget::Table::HeaderView :
	public QHeaderView
{
private:
	Qt::Orientation _orientation = Qt::Orientation::Vertical;
	int _selected_index = -1;
	Qt::AlignmentFlag _text_alignment{};
	widget::Padding _padding{10, 5, 10, 5};
	int _original_default_section_size = defaultSectionSize();

protected:
	void paintSection(QPainter *painter, QRect const &rect, int logicalIndex) const override;

	QSize sizeHint() const override;

public:
	HeaderView(Qt::Orientation orientation)
		: QHeaderView(orientation, nullptr)
	{
		_orientation = orientation;
		setSectionResizeMode(QHeaderView::ResizeMode::Fixed);

		if (orientation == Qt::Orientation::Vertical)
		{
			// 派生 QHeaderView 类，自定义绘制后，行标题老是不够高，所以就在这里设置默认
			// 的 Section 尺寸，对于行标题来说就是高度。让高度比默认值增加 10.
			//
			// 对于列标题来说，Section 大小控制的是宽度。
			setDefaultSectionSize(_original_default_section_size + 10);
		}

		if (orientation == Qt::Orientation::Vertical)
		{
			// 是垂直方向，即行标题。
			_text_alignment = widget::AlignmentFlag{
				Qt::AlignmentFlag::AlignRight,
				Qt::AlignmentFlag::AlignVCenter,
			};
		}
		else
		{
			// 是水平方向，即列标题。
			_text_alignment = widget::AlignmentFlag{
				Qt::AlignmentFlag::AlignHCenter,
				Qt::AlignmentFlag::AlignVCenter,
			};
		}
	}

	void SetSelectedIndex(int index)
	{
		_selected_index = index;
	}

	///
	/// @brief 标题单元格的内边距。
	///
	/// @return
	///
	widget::Padding Padding() const
	{
		return _padding;
	}

	///
	/// @brief 设置标题单元格的内边距。
	///
	/// @param value
	///
	void SetPadding(widget::Padding const &value)
	{
		_padding = value;
	}

	Qt::AlignmentFlag TextAlignment() const
	{
		return _text_alignment;
	}

	void SetTextAlignment(Qt::AlignmentFlag value)
	{
		_text_alignment = value;
	}

	///
	/// @brief 表头方向。
	///
	/// @return Qt::Orientation::Vertical 是垂直方向的表头，即行标题。
	/// Qt::Orientation::Horizontal 是水平方向的表头，即列标题。
	///
	Qt::Orientation Orientation() const
	{
		return _orientation;
	}

	///
	/// @brief 默认的节尺寸。
	///
	/// @note 对于行标题，指的是高度。
	/// @note 对于列标题，指的是宽度。
	///
	/// @return
	///
	int DefaultSectionSize() const
	{
		return defaultSectionSize();
	}
};
