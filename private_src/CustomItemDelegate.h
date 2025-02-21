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
				   QModelIndex const &index) const override;

		QSize sizeHint(QStyleOptionViewItem const &option, QModelIndex const &index) const override;
	};
} // namespace widget
