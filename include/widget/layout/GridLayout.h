#pragma once
#include "qnamespace.h"
#include <qgridlayout.h>
#include <widget/layout/GridPosition.h>
#include <widget/layout/Padding.h>

namespace widget
{
	/**
	 * @brief 网格布局。
	 *
	 */
	class GridLayout
	{
	private:
		std::shared_ptr<QGridLayout> _grid_layout{};

	public:
		// 构造函数

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
		// 添加控件

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
		/**
		 * @brief 移除指定的控件。
		 *
		 * @param widget 要从布局中移除的控件。
		 *@note 注意，此控件只是从布局中消失了，并不会被 delete.
		 */
		void RemoveWidget(QWidget *widget);

		/**
		 * @brief 移除指定位置的控件。
		 *
		 * @param row 要被移除的控件的行号。
		 * @param column 要被移除的控件的列号。
		 */
		void RemoveWidget(int row, int column);

		/**
		 * @brief 获取指定位置的控件。
		 *
		 * @param row
		 * @param column
		 * @return QWidget* 找到则返回控件的指针。如果指定位置没有控件，则返回空指针。
		 */
		QWidget *GetWidget(int row, int column) const;

		/**
		 * @brief 获取指定控件在网格中的位置。
		 *
		 * @param widget 要查找位置的控件。
		 * @return widget::GridPosition
		 *
		 * @exception runtime_error 如果找不到控件，将抛出异常。
		 */
		widget::GridPosition GetWidgetPosition(QWidget *widget);

	public:
		// 缩放因子

		/**
		 * @brief 行缩放因子。
		 *
		 * @param row
		 * @return int
		 */
		int RowStretch(int row) const;

		/**
		 * @brief 设置行缩放因子。
		 *
		 * @param row
		 * @param stretch
		 */
		void SetRowStretch(int row, int stretch);

		/**
		 * @brief 列缩放因子。
		 *
		 * @param column
		 * @return int
		 */
		int ColumnStretch(int column) const;

		/**
		 * @brief 设置列缩放因子。
		 *
		 * @param column
		 * @param stretch
		 */
		void SetColumnStretch(int column, int stretch);

	public:
		// 样式

		/**
		 * @brief 网格盒子的对齐方式。
		 *
		 * @return Qt::AlignmentFlag
		 */
		Qt::AlignmentFlag Alignment() const;

		/**
		 * @brief 设置网格盒子的对齐方式。
		 *
		 * @note 默认是展开。即网格盒子充满整个上级容器。
		 *
		 * @note 设置为 Qt::AlignmentFlag::AlignTop 可以让网格每一行都适应内容的高度，而不是整体撑开，
		 * 导致每一行都因为内容无法充满格子而有大量空白。
		 *
		 * @param alignment 对齐方式。
		 */
		void SetAlignment(Qt::AlignmentFlag alignment);

		/**
		 * @brief 网格盒子的内边距。
		 *
		 * @return widget::Padding
		 */
		widget::Padding Padding() const;

		/**
		 * @brief 设置网格盒子的内边距。
		 *
		 * @param value
		 */
		void SetPadding(widget::Padding const &value);
	};
} // namespace widget
