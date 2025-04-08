#include "FormTableBoxItem.h"
#include "qlabel.h"

/* #region 构造函数 */

widget::FormTableBoxItem::FormTableBoxItem(std::shared_ptr<QWidget> const &left,
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

widget::FormTableBoxItem::FormTableBoxItem(std::string const &left_label_text,
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

std::shared_ptr<QWidget> widget::FormTableBoxItem::LeftWidget() const
{
	return _left;
}

std::shared_ptr<QWidget> widget::FormTableBoxItem::RightWidget() const
{
	return _right;
}
