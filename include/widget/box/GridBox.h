#pragma once
#include "base/container/List.h"
#include "base/string/define.h"
#include "GridBoxItem.h"
#include "LabelDataGridItem.h"
#include "LabelDataUnitGridItem.h"
#include "qgridlayout.h"
#include "qwidget.h"
#include "widget/layout/Padding.h"
#include <algorithm>
#include <cstdint>
#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <vector>

namespace widget
{
	///
	/// @brief 网格盒子。
	///
	///
	class GridBox :
		public QWidget
	{
	private:
		QGridLayout _grid_layout{this};
		base::List<widget::GridBoxItem> _item_list{};

	public:
		/* #region 构造函数 */

		GridBox()
		{
			_grid_layout.setSpacing(10);
			SetPadding(widget::Padding{0});
		}

		GridBox(std::initializer_list<widget::GridBoxItem> const &items)
			: GridBox()
		{
			try
			{
				for (widget::GridBoxItem const &item : items)
				{
					AddItem(item);
				}
			}
			catch (std::exception const &e)
			{
				throw std::runtime_error{CODE_POS_STR + e.what()};
			}
			catch (...)
			{
				throw std::runtime_error{CODE_POS_STR + "未知的异常。"};
			}
		}

		GridBox(std::initializer_list<widget::LabelDataUnitGridItem> const &items)
			: GridBox()
		{
			try
			{
				int max_column = 0;

				for (widget::LabelDataUnitGridItem const &item : items)
				{
					max_column = std::max(max_column, item.Column());

					widget::GridBoxItem label{
						item.Row(),
						item.Column() * 3,
						item.Lable(),
					};

					widget::GridBoxItem data{
						item.Row(),
						item.Column() * 3 + 1,
						item.Data(),
					};

					widget::GridBoxItem unit{
						item.Row(),
						item.Column() * 3 + 2,
						item.Unit(),
					};

					AddItem(label);
					AddItem(data);
					AddItem(unit);
				}

				for (int i = 0; i <= max_column; i++)
				{
					SetColumnStretch(i * 3 + 0, 0);
					SetColumnStretch(i * 3 + 1, 1);
					SetColumnStretch(i * 3 + 2, 0);
				}

				SetAlignment(Qt::AlignmentFlag::AlignTop);
			}
			catch (std::exception const &e)
			{
				throw std::runtime_error{CODE_POS_STR + e.what()};
			}
			catch (...)
			{
				throw std::runtime_error{CODE_POS_STR + "未知的异常。"};
			}
		}

		GridBox(std::initializer_list<widget::LabelDataGridItem> const &items)
			: GridBox()
		{
			try
			{
				int max_column = 0;

				for (widget::LabelDataGridItem const &item : items)
				{
					max_column = std::max(max_column, item.Column());

					widget::GridBoxItem label{
						item.Row(),
						item.Column() * 2,
						item.Lable(),
					};

					widget::GridBoxItem data{
						item.Row(),
						item.Column() * 2 + 1,
						item.Data(),
					};

					AddItem(label);
					AddItem(data);
				}

				for (int i = 0; i <= max_column; i++)
				{
					SetColumnStretch(i * 2 + 0, 0);
					SetColumnStretch(i * 2 + 1, 1);
				}

				SetAlignment(Qt::AlignmentFlag::AlignTop);
			}
			catch (std::exception const &e)
			{
				throw std::runtime_error{CODE_POS_STR + e.what()};
			}
			catch (...)
			{
				throw std::runtime_error{CODE_POS_STR + "未知的异常。"};
			}
		}

		/* #endregion */

		void AddItem(widget::GridBoxItem const &item)
		{
			for (auto &item_list_item : _item_list)
			{
				if (item_list_item.Widget() == item.Widget())
				{
					throw std::invalid_argument{CODE_POS_STR + "不能重复添加同一个对象。"};
				}
			}

			_grid_layout.addWidget(item.Widget().get(),
								   item.Row(),
								   item.Column(),
								   item.RowSpan(),
								   item.ColumnSpan(),
								   item.Align());

			_item_list.Add(item);
		}

		///
		/// @brief 设置一个项目。会移除同一个格子中的旧项目，然后才添加 item.
		///
		/// @param item
		///
		void SetItem(widget::GridBoxItem const &item)
		{
			RemoveWidget(item.Row(), item.Column());

			_grid_layout.addWidget(item.Widget().get(),
								   item.Row(),
								   item.Column(),
								   item.RowSpan(),
								   item.ColumnSpan(),
								   item.Align());

			_item_list.Add(item);
		}

		/* #region 移除控件 */

		///
		/// @brief 通过行列移除控件。
		///
		/// @param row
		/// @param column
		///
		void RemoveWidget(int row, int column)
		{
			for (int i = _item_list.Count() - 1; i >= 0; i--)
			{
				if (_item_list[i].Row() == row && _item_list[i].Column() == column)
				{
					_grid_layout.removeWidget(_item_list[i].Widget().get());
					_item_list.RemoveAt(i);

					// 移除后不返回。因为可能有多个控件同时层叠放置在同一个格子。
				}
			}
		}

		///
		/// @brief 移除控件。
		///
		/// @param widget
		///
		void RemoveWidget(std::shared_ptr<QWidget> widget)
		{
			if (widget == nullptr)
			{
				return;
			}

			for (int i = _item_list.Count() - 1; i >= 0; i--)
			{
				if (_item_list[i].Widget() == widget)
				{
					_grid_layout.removeWidget(widget.get());
					_item_list.RemoveAt(i);
					return;
				}
			}
		}

		///
		/// @brief 清空所有控件。
		///
		///
		void ClearWidgets()
		{
			for (auto &item : _item_list)
			{
				_grid_layout.removeWidget(item.Widget().get());
			}

			_item_list.Clear();
		}

		/* #endregion */

		/* #region 缩放因子 */

		///
		/// @brief 行缩放因子。
		///
		/// @param row
		/// @return int
		///
		int RowStretch(int row) const
		{
			return _grid_layout.rowStretch(row);
		}

		///
		/// @brief 设置行缩放因子。
		///
		/// @param row
		/// @param stretch
		///
		void SetRowStretch(int row, int stretch)
		{
			_grid_layout.setRowStretch(row, stretch);
		}

		///
		/// @brief 批量设置行缩放因子。
		///
		/// @param stretch_vec
		///
		void SetRowStretch(std::vector<int> const &stretch_vec)
		{
			for (uint32_t i = 0; i < stretch_vec.size(); i++)
			{
				SetRowStretch(i, stretch_vec[i]);
			}
		}

		///
		/// @brief 列缩放因子。
		///
		/// @param column
		/// @return int
		///
		int ColumnStretch(int column) const
		{
			return _grid_layout.columnStretch(column);
		}

		///
		/// @brief 设置列缩放因子。
		///
		/// @param column
		/// @param stretch
		///
		void SetColumnStretch(int column, int stretch)
		{
			_grid_layout.setColumnStretch(column, stretch);
		}

		///
		/// @brief 批量设置列缩放因子。
		///
		/// @param stretch_vec
		///
		void SetColumnStretch(std::vector<int> const &stretch_vec)
		{
			for (uint32_t i = 0; i < stretch_vec.size(); i++)
			{
				SetColumnStretch(i, stretch_vec[i]);
			}
		}

		/* #endregion */

		/* #region 网格盒子的样式 */

		///
		/// @brief 网格盒子的对齐方式。
		///
		/// @return
		///
		Qt::AlignmentFlag Alignment() const
		{
			return static_cast<Qt::AlignmentFlag>(_grid_layout.alignment().toInt());
		}

		///
		/// @brief 设置网格盒子的对齐方式。
		///
		/// @note 默认是展开。即网格盒子充满整个上级容器。
		///
		/// @note 设置为 Qt::AlignmentFlag::AlignTop 可以让网格每一行都适应内容的高度，而不是整体撑开，
		/// 导致每一行都因为内容无法充满格子而有大量空白。
		///
		/// @param alignment 对齐方式。
		///
		void SetAlignment(Qt::AlignmentFlag alignment)
		{
			_grid_layout.setAlignment(alignment);
		}

		///
		/// @brief 网格盒子的内边距。
		///
		/// @return
		///
		widget::Padding Padding() const
		{
			QMargins qmargin = _grid_layout.contentsMargins();

			return widget::Padding{
				qmargin.left(),
				qmargin.top(),
				qmargin.right(),
				qmargin.bottom(),
			};
		}

		///
		/// @brief 设置网格盒子的内边距。
		///
		/// @param value
		///
		void SetPadding(widget::Padding const &value)
		{
			_grid_layout.setContentsMargins(value.Left(), value.Top(),
											value.Right(), value.Bottom());
		}

		/* #endregion */

		/* #region 网格盒子的行列间距 */

		///
		/// @brief 网格盒子的行列间距。
		///
		/// @return
		///
		int Spacing() const
		{
			return _grid_layout.spacing();
		}

		///
		/// @brief 设置网格盒子的行列间距。
		///
		/// @param value
		///
		void SetSpacing(int value)
		{
			_grid_layout.setSpacing(value);
		}

		///
		/// @brief 网格盒子的水平间距。
		///
		/// @return
		///
		int HorizontalSpacing() const
		{
			return _grid_layout.horizontalSpacing();
		}

		///
		/// @brief 设置网格盒子的水平间距。
		///
		/// @param value
		///
		void SetHorizontalSpacing(int value)
		{
			_grid_layout.setHorizontalSpacing(value);
		}

		///
		/// @brief 网格盒子的垂直间距。
		///
		/// @return
		///
		int VerticalSpacing() const
		{
			return _grid_layout.verticalSpacing();
		}

		///
		/// @brief 设置网格盒子的垂直间距。
		///
		/// @param value
		///
		void SetVerticalSpacing(int value)
		{
			_grid_layout.setVerticalSpacing(value);
		}

		/* #endregion */
	};

} // namespace widget
