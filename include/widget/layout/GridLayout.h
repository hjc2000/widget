#pragma once
#include <memory>
#include <qgridlayout.h>
#include <qwidget.h>
#include <widget/layout/Padding.h>

namespace widget
{
	class GridLayout
	{
	private:
		std::shared_ptr<QGridLayout> _grid_layout{};

	public:
		/**
		 * @brief Construct a new Grid Layout object
		 *
		 * @param parent
		 */
		GridLayout(QWidget *parent);

		/**
		 * @brief Construct a new Grid Layout object
		 *
		 * @param parent
		 * @param padding
		 */
		GridLayout(QWidget *parent, widget::Padding const &padding);

	public:
		/**
		 * @brief 添加一个控件。
		 *
		 * @param widget
		 * @param row 要添加到网格中的哪一行。
		 * @param column 要添加到网格中的哪一列。
		 */
		void AddWidget(QWidget *widget, int row, int column);

		/**
		 * @brief
		 *
		 * @param widget
		 * @param row
		 * @param column
		 * @param align
		 */
		void AddWidget(QWidget *widget, int row, int column, Qt::AlignmentFlag align);

		/**
		 * @brief
		 *
		 * @param widget
		 * @param row
		 * @param column
		 * @param row_span
		 * @param column_span
		 */
		void AddWidget(QWidget *widget, int row, int column, int row_span, int column_span);

		/**
		 * @brief
		 *
		 * @param widget
		 * @param row
		 * @param column
		 * @param row_span
		 * @param column_span
		 * @param align
		 */
		void AddWidget(QWidget *widget, int row, int column, int row_span, int column_span, Qt::AlignmentFlag align);

	public:
		int RowStretch(int row) const;
		void SetRowStretch(int row, int stretch);

		int ColumnStretch(int column) const;
		void SetColumnStretch(int column, int stretch);
	};
} // namespace widget
