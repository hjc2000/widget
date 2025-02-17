#include "Table.h"
#include <base/string/Parse.h>
#include <iostream>
#include <QAbstractTableModel>
#include <QApplication>
#include <QPainter>
#include <QStyledItemDelegate>
#include <string>
#include <widget/Conversion.h>
#include <widget/Submit.h>

#pragma region CustomItemDelegate

namespace
{
	/// @brief 按照自定义的方式绘制单元格。
	class CustomItemDelegate :
		public QStyledItemDelegate
	{
	public:
		using QStyledItemDelegate::QStyledItemDelegate;

		void paint(QPainter *painter,
				   QStyleOptionViewItem const &option,
				   QModelIndex const &index) const override
		{
			// 创建一个新的 QStyleOptionViewItem 并初始化
			QStyleOptionViewItem new_option = option;
			initStyleOption(&new_option, index);

			QString text = index.data(Qt::DisplayRole).toString();

			QTextOption text_option{};

			text_option.setAlignment(Qt::AlignmentFlag::AlignLeft |
									 Qt::AlignmentFlag::AlignVCenter);

			QRect text_rect = new_option.rect;
			text_rect.setX(text_rect.x() + 5);

			if (new_option.state & QStyle::State_Selected)
			{
				if (new_option.state & QStyle::State_Active)
				{
					painter->fillRect(new_option.rect, QColor{204, 232, 255});
					painter->drawText(text_rect, text, text_option);
				}
				else
				{
					painter->fillRect(new_option.rect, QColor{240, 240, 240});
					painter->drawText(text_rect, text, text_option);
				}
			}
			else
			{
				painter->fillRect(new_option.rect, Qt::GlobalColor::white);
				painter->drawText(text_rect, text, text_option);
			}
		}
	};

	/// @brief 通过调色盘设置单元格成为焦点和失去焦点时的颜色。
	class CustomItemDelegate1 :
		public QStyledItemDelegate
	{
	public:
		using QStyledItemDelegate::QStyledItemDelegate;

		void paint(QPainter *painter,
				   QStyleOptionViewItem const &option,
				   QModelIndex const &index) const override
		{
			if (option.state & QStyle::State_HasFocus)
			{
				std::cout << "是焦点" << std::endl;

				// 创建一个新的 QStyleOptionViewItem 并初始化
				QStyleOptionViewItem new_option = option;
				initStyleOption(&new_option, index);

				// 修改 Highlight 和 HighlightedText 颜色
				QPalette new_palette = new_option.palette;

				// 单元格获得焦点时的背景颜色。
				new_palette.setColor(QPalette::ColorGroup::Active,
									 QPalette::ColorRole::Highlight,
									 QColor{204, 232, 255});

				// 单元格从拥有焦点变成失去焦点时的背景颜色。
				new_palette.setColor(QPalette::ColorGroup::Inactive,
									 QPalette::ColorRole::Highlight,
									 QColor{240, 240, 240});

				// 单元格获得焦点时的文字颜色。
				new_palette.setColor(QPalette::ColorGroup::Active,
									 QPalette::ColorRole::HighlightedText,
									 Qt::GlobalColor::black);

				// 单元格从拥有焦点变成失去焦点时的文字颜色。
				new_palette.setColor(QPalette::ColorGroup::Inactive,
									 QPalette::ColorRole::HighlightedText,
									 Qt::GlobalColor::black);

				// 应用修改后的 palette
				new_option.palette = new_palette;

				// 调用基类绘制方法
				QStyledItemDelegate::paint(painter, new_option, index);
			}
			else
			{
				// 调用基类绘制方法
				QStyledItemDelegate::paint(painter, option, index);
			}
		}
	};
} // namespace

#pragma endregion

#pragma region 重写事件

void widget::Table::enterEvent(QEnterEvent *event)
{
	QTableView::enterEvent(event);

	static bool first_time = true;
	if (first_time)
	{
		first_time = false;
		QHeaderView *header = horizontalHeader();
		header->setSectionResizeMode(QHeaderView::Interactive);
	}
}

void widget::Table::leaveEvent(QEvent *event)
{
	QTableView::leaveEvent(event);
}

#pragma endregion

#pragma region 初始化函数

void widget::Table::ClearInitialFocus()
{
	clearFocus();
	setCurrentIndex(QModelIndex{});
}

void widget::Table::SetAsPerPixelScroll()
{
	setHorizontalScrollMode(ScrollMode::ScrollPerPixel);
	setVerticalScrollMode(ScrollMode::ScrollPerPixel);
}

#pragma endregion

widget::Table::Table(QWidget *parent)
	: QTableView(parent)
{
	setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);

	{
		// 设置选择行为为选择单元格
		setSelectionBehavior(SelectionBehavior::SelectItems);
		setSelectionMode(SelectionMode::SingleSelection);
	}

	SetAsPerPixelScroll();

	// 设置单元格绘制代理，按照自定义的方式绘制单元格。
	setItemDelegate(new CustomItemDelegate{this});
}

#pragma region setModel

void widget::Table::setModel(QAbstractItemModel *model)
{
	QTableView::setModel(model);
	ClearInitialFocus();

	{
		// 设置列头自适应大小。
		QHeaderView *header = horizontalHeader();
		header->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
	}

	{
		QHeaderView *header = horizontalHeader();

		// 允许用户移动列
		header->setSectionsMovable(true);

		// 允许用户点击列头
		header->setSectionsClickable(true);
	}
}

void widget::Table::setModel(QAbstractItemModel *model,
							 std::vector<QHeaderView::ResizeMode> resize_modes)
{
	setModel(model);
	SetResizeModes(resize_modes);
}

#pragma endregion

void widget::Table::SetResizeModes(std::vector<QHeaderView::ResizeMode> resize_modes)
{
	QHeaderView *header = horizontalHeader();
	int count = std::min(header->count(), static_cast<int>(resize_modes.size()));
	for (int i = 0; i < count; ++i)
	{
		header->setSectionResizeMode(i, resize_modes[i]);
	}
}
