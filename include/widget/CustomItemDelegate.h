#pragma once
#include <QStyledItemDelegate>

namespace widget
{
	class CustomItemDelegate : public QStyledItemDelegate
	{
	public:
		using QStyledItemDelegate::QStyledItemDelegate;

		void paint(QPainter *painter, QStyleOptionViewItem const &option, QModelIndex const &index) const override;
	};
} // namespace widget
