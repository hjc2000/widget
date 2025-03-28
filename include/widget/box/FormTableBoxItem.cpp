#include "FormTableBoxItem.h"
#include "qlabel.h"

void widget::FormTableBoxItem::Initialize()
{
	if (_left == nullptr)
	{
		throw new std::runtime_error{CODE_POS_STR + "_left 不能为空指针。"};
	}

	if (_right == nullptr)
	{
		throw new std::runtime_error{CODE_POS_STR + "_right 不能为空指针。"};
	}

	// 设置成 QSizePolicy::Policy::Preferred 允许网格将内容拉伸到充满网格。
	_left->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
	_right->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
}

/* #region 构造函数 */

widget::FormTableBoxItem::FormTableBoxItem(std::shared_ptr<QWidget> const &left,
										   std::shared_ptr<QWidget> const &right)
	: _left(left),
	  _right(right)
{
	Initialize();
}

widget::FormTableBoxItem::FormTableBoxItem(std::string const &left_label_text,
										   std::shared_ptr<QWidget> const &right)
{
	_left = std::shared_ptr<QLabel>{new QLabel{left_label_text.c_str()}};
	_right = right;

	Initialize();
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
