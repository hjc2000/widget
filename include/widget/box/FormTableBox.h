#pragma once
#include "GridBox.h"
#include "GridBoxItem.h"
#include "QWidget"
#include "widget/box/FormTableBoxItem.h"
#include "widget/layout/Padding.h"
#include "widget/layout/VBoxLayout.h"

namespace widget
{
	///
	/// @brief 表单布局的盒子。
	///
	///
	class FormTableBox :
		public QWidget
	{
	private:
		widget::VBoxLayout _layout{this, widget::Padding{0}};
		widget::GridBox _box{};

	public:
		/* #region 构造函数 */

		FormTableBox()
		{
			_layout.AddWidget(&_box);

			// 第 0 列的增长因子为 0，不允许增长，而是根据内容调整大小。
			_box.SetColumnStretch(0, 0);

			// 第 1 列的增长因子为 1.
			//
			// 凡是增长因子不为 0 的，都会根据因子的比例去分配剩余的宽度。
			// 这里一共 2 列，其中第 0 列增长因子为 0，所以第 1 列就占据所有剩余宽度。
			_box.SetColumnStretch(1, 1);

			// 让表单中每一行从顶端开始一行一行往下排列。
			_box.SetAlignment(Qt::AlignmentFlag::AlignTop);
		}

		///
		/// @brief 构造函数。构造的过程中添加一系列表单项到盒子中。
		///
		/// @param items
		///
		FormTableBox(std::initializer_list<widget::FormTableBoxItem> const &items)
			: FormTableBox()
		{
			try
			{
				SetItem(items);
			}
			catch (std::exception const &e)
			{
				throw new std::runtime_error{CODE_POS_STR + e.what()};
			}
		}

		/* #endregion */

		///
		/// @brief 设置一条表单项。
		///
		/// @param row 要将表单项设置到哪一行。
		///		@note 如果该行已经有表单项了，会先移除旧的表单项。
		///
		/// @param item
		///
		void SetItem(int row, widget::FormTableBoxItem const &item)
		{
			if (item.LeftWidget() == nullptr)
			{
				throw new std::runtime_error{CODE_POS_STR + "item.LeftWidget() 不能为空指针。"};
			}

			if (item.RightWidget() == nullptr)
			{
				throw new std::runtime_error{CODE_POS_STR + "item.RightWidget() 不能为空指针。"};
			}

			try
			{
				_box.SetItem(widget::GridBoxItem{row, 0, item.LeftWidget()});
				_box.SetItem(widget::GridBoxItem{row, 1, item.RightWidget()});
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

		///
		/// @brief 设置一系列表单项。
		///
		/// @note 从第 0 行开始添加，如果添加到某一行，该行已经有一个表单项了，则会先移除旧的
		/// 表单项，然后添加。
		///
		/// @param items
		///
		void SetItem(std::initializer_list<widget::FormTableBoxItem> const &items)
		{
			int i = 0;

			try
			{
				for (widget::FormTableBoxItem const &item : items)
				{
					SetItem(i++, item);
				}
			}
			catch (std::exception const &e)
			{
				std::string message = CODE_POS_STR +
									  std::format("添加到第 {} 个项目时引发异常", i) +
									  e.what();

				throw new std::runtime_error{message};
			}
		}

		///
		/// @brief 移除某一行的表单项。
		///
		/// @param row
		///
		void RemoveItem(int row)
		{
			_box.RemoveWidget(row, 0);
			_box.RemoveWidget(row, 1);
		}

		///
		/// @brief 清空所有表单项。
		///
		///
		void ClearItems()
		{
			_box.ClearWidgets();
		}

		///
		/// @brief 表单盒子内边距。
		///
		/// @return
		///
		widget::Padding Padding() const
		{
			return _box.Padding();
		}

		///
		/// @brief 设置表单盒子内边距。
		///
		/// @param value
		///
		void SetPadding(widget::Padding const &value)
		{
			_box.SetPadding(value);
		}
	};

} // namespace widget
