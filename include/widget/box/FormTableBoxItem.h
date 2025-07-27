#pragma once
#include "base/string/define.h"
#include "qlabel.h"
#include "qwidget.h"
#include <memory>
#include <string>

namespace widget
{
	///
	/// @brief 表单的项目。
	///
	///
	class FormTableBoxItem
	{
	private:
		std::shared_ptr<QWidget> _left{};
		std::shared_ptr<QWidget> _right{};

	public:
		/* #region 构造函数 */

		///
		/// @brief 构造出来的 _left 和 _right 都是空指针，不能被添加到表单盒子中，
		/// 添加了会引发异常。
		///
		FormTableBoxItem() = default;

		///
		/// @brief 构造一个左右两边都是自定义控件的表单项。
		///
		/// @param left
		/// @param right
		///
		FormTableBoxItem(std::shared_ptr<QWidget> const &left,
						 std::shared_ptr<QWidget> const &right)
		{
			if (left == nullptr)
			{
				throw new std::runtime_error{CODE_POS_STR + "left 不能为空指针。"};
			}

			if (right == nullptr)
			{
				throw new std::runtime_error{CODE_POS_STR + "right 不能为空指针。"};
			}

			_left = left;
			_right = right;
		}

		///
		/// @brief 构造一个左边是文本标签，右边是自定义控件的表单项。
		///
		/// @param left_label_text 文本标签的文本。
		/// @param right 自定义控件。
		///
		FormTableBoxItem(std::string const &left_label_text,
						 std::shared_ptr<QWidget> const &right)
		{
			if (right == nullptr)
			{
				throw new std::runtime_error{CODE_POS_STR + "right 不能为空指针。"};
			}

			_left = std::shared_ptr<QLabel>{new QLabel{left_label_text.c_str()}};
			_right = right;
		}

		/* #endregion */

		///
		/// @brief 左侧控件。
		///
		/// @return
		///
		std::shared_ptr<QWidget> LeftWidget() const
		{
			return _left;
		}

		///
		/// @brief 右侧控件。
		///
		/// @return
		///
		std::shared_ptr<QWidget> RightWidget() const
		{
			return _right;
		}
	};

} // namespace widget
