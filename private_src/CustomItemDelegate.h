#pragma once

#include "qpainter.h"
#include "qstyleditemdelegate.h"
#include "qstyleoption.h"
#include "qtextoption.h"

namespace widget
{
	/// @brief 按照自定义的方式绘制单元格。
	class CustomItemDelegate :
		public QStyledItemDelegate
	{
	private:
		int _padding = 10;

	public:
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
			text_rect.adjust(_padding, 0, -_padding, 0);

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

		QSize sizeHint(QStyleOptionViewItem const &option, QModelIndex const &index) const override
		{
			QSize size = QStyledItemDelegate::sizeHint(option, index);

			// 获取文本宽度并加上左右内边距
			QFontMetrics fm(option.font);
			QString text = index.data(Qt::DisplayRole).toString();
			int textWidth = fm.horizontalAdvance(text) + 2 * _padding;
			size.setWidth(qMax(size.width(), textWidth));
			return size;
		}
	};
} // namespace widget
