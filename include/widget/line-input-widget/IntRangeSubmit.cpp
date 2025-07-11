#include "IntRangeSubmit.h"
#include "base/string/define.h"
#include "base/string/Parse.h"
#include <iostream>

bool widget::IntRangeSubmit::TryParseLeftValue(int64_t &out)
{
	try
	{
		out = base::ParseInt64(_range_submit.LeftTextStdString());
		return true;
	}
	catch (std::exception const &e)
	{
		SetLeftInvalidInputStyle(true);
		std::cerr << CODE_POS_STR + e.what() << std::endl;
	}
	catch (...)
	{
		SetLeftInvalidInputStyle(true);
		std::cerr << CODE_POS_STR + "发生了未知错误" << std::endl;
	}

	return false;
}

bool widget::IntRangeSubmit::TryParseRightValue(int64_t &out)
{
	try
	{
		out = base::ParseInt64(_range_submit.RightTextStdString());
		return true;
	}
	catch (std::exception const &e)
	{
		SetRightInvalidInputStyle(true);
		std::cerr << CODE_POS_STR + e.what() << std::endl;
	}
	catch (...)
	{
		SetRightInvalidInputStyle(true);
		std::cerr << CODE_POS_STR + "发生了未知错误" << std::endl;
	}

	return false;
}

void widget::IntRangeSubmit::CheckLeftRightValues(int64_t left_value, int64_t right_value)
{
	if (left_value > right_value)
	{
		std::cerr << CODE_POS_STR + "左侧值不能大于右侧值。" << std::endl;
		SetLeftInvalidInputStyle(true);
		SetRightInvalidInputStyle(true);
		return;
	}

	if (left_value < _min)
	{
		std::cerr << CODE_POS_STR + "左侧值不能小于最小值。" << std::endl;
		SetLeftInvalidInputStyle(true);
		return;
	}

	if (right_value > _max)
	{
		std::cerr << CODE_POS_STR + "右侧值不能大于最大值。" << std::endl;
		SetRightInvalidInputStyle(true);
		return;
	}

	// 数据合法
	_left_value = left_value;
	_right_value = right_value;
	SetLeftInvalidInputStyle(false);
	SetRightInvalidInputStyle(false);
}

void widget::IntRangeSubmit::OnSubmit()
{
	int64_t left_value = 0;
	int64_t right_value = 0;
	bool parse_left_value_result = TryParseLeftValue(left_value);
	bool parse_right_value_result = TryParseRightValue(right_value);

	if (!(parse_left_value_result && parse_right_value_result))
	{
		return;
	}

	CheckLeftRightValues(left_value, right_value);

	try
	{
		_submit_event.Invoke();
	}
	catch (std::exception const &e)
	{
		std::cerr << CODE_POS_STR + e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << CODE_POS_STR + "发生了未知错误" << std::endl;
	}
}

widget::IntRangeSubmit::IntRangeSubmit()
{
	_layout.AddWidget(&_range_submit);

	_range_submit.SubmitEvent().Subscribe([this]()
										  {
											  OnSubmit();
										  });

	_range_submit.SetLeftText(std::to_string(_left_value));
	_range_submit.SetRightText(std::to_string(_right_value));
}

widget::IntRangeSubmit::IntRangeSubmit(int64_t min, int64_t max)
	: IntRangeSubmit()
{
	if (min > max)
	{
		throw std::invalid_argument{CODE_POS_STR + "最小值不能大于最大值。"};
	}

	_min = min;
	_max = max;
}

/* #region 最大最小值 */

int64_t widget::IntRangeSubmit::MinValue() const
{
	return _min;
}

void widget::IntRangeSubmit::SetMinValue(int64_t value)
{
	_min = value;
}

int64_t widget::IntRangeSubmit::MaxValue() const
{
	return _max;
}

void widget::IntRangeSubmit::SetMaxValue(int64_t value)
{
	_max = value;
}

/* #endregion */

/* #region 区间 */

int64_t widget::IntRangeSubmit::LeftValue() const
{
	return _left_value;
}

int64_t widget::IntRangeSubmit::RightValue() const
{
	return _right_value;
}

base::ClosedInterval<int64_t> widget::IntRangeSubmit::Interval() const
{
	return base::ClosedInterval<int64_t>{LeftValue(), RightValue()};
}

/* #endregion */

base::IEvent<> &widget::IntRangeSubmit::SubmitEvent()
{
	return _submit_event;
}

/* #region 输入非法样式 */

void widget::IntRangeSubmit::SetLeftInvalidInputStyle(bool is_invalid)
{
	_range_submit.SetLeftInvalidInputStyle(is_invalid);
}

void widget::IntRangeSubmit::SetRightInvalidInputStyle(bool is_invalid)
{
	_range_submit.SetRightInvalidInputStyle(is_invalid);
}

/* #endregion */

/* #region PlaceholderText */

QString widget::IntRangeSubmit::LeftPlaceholderText() const
{
	return _range_submit.LeftPlaceholderText();
}

void widget::IntRangeSubmit::SetLeftPlaceholderText(QString const &value)
{
	_range_submit.SetLeftPlaceholderText(value);
}

void widget::IntRangeSubmit::SetLeftPlaceholderText(std::string const &value)
{
	_range_submit.SetLeftPlaceholderText(value);
}

void widget::IntRangeSubmit::SetLeftPlaceholderText(char const *value)
{
	_range_submit.SetLeftPlaceholderText(value);
}

std::string widget::IntRangeSubmit::LeftPlaceholderTextStdString() const
{
	return _range_submit.LeftPlaceholderTextStdString();
}

QString widget::IntRangeSubmit::RightPlaceholderText() const
{
	return _range_submit.RightPlaceholderText();
}

void widget::IntRangeSubmit::SetRightPlaceholderText(QString const &value)
{
	_range_submit.SetRightPlaceholderText(value);
}

void widget::IntRangeSubmit::SetRightPlaceholderText(std::string const &value)
{
	_range_submit.SetRightPlaceholderText(value);
}

void widget::IntRangeSubmit::SetRightPlaceholderText(char const *value)
{
	_range_submit.SetRightPlaceholderText(value);
}

std::string widget::IntRangeSubmit::RightPlaceholderTextStdString() const
{
	return _range_submit.RightPlaceholderTextStdString();
}

/* #endregion */

/* #region 输入框的文本 */

QString widget::IntRangeSubmit::LeftText() const
{
	return _range_submit.LeftText();
}

void widget::IntRangeSubmit::SetLeftText(QString const &value)
{
	_range_submit.SetLeftText(value);
}

void widget::IntRangeSubmit::SetLeftText(std::string const &value)
{
	_range_submit.SetLeftText(value);
}

void widget::IntRangeSubmit::SetLeftText(char const *value)
{
	_range_submit.SetLeftText(value);
}

std::string widget::IntRangeSubmit::LeftTextStdString() const
{
	return _range_submit.LeftTextStdString();
}

QString widget::IntRangeSubmit::RightText() const
{
	return _range_submit.RightText();
}

void widget::IntRangeSubmit::SetRightText(QString const &value)
{
	_range_submit.SetRightText(value);
}

void widget::IntRangeSubmit::SetRightText(std::string const &value)
{
	_range_submit.SetRightText(value);
}

void widget::IntRangeSubmit::SetRightText(char const *value)
{
	_range_submit.SetRightText(value);
}

std::string widget::IntRangeSubmit::RightTextStdString() const
{
	return _range_submit.RightTextStdString();
}

/* #endregion */
