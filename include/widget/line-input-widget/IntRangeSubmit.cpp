#include "IntRangeSubmit.h"

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

void widget::IntRangeSubmit::SetLeftPlaceholderText(char const *value)
{
	_range_submit.SetLeftPlaceholderText(value);
}

std::string widget::IntRangeSubmit::LeftPlaceholderTextStdString() const
{
	return _range_submit.LeftPlaceholderTextStdString();
}

void widget::IntRangeSubmit::SetRightPlaceholderText(char const *value)
{
	_range_submit.SetRightPlaceholderText(value);
}

/* #endregion */

/* #region 输入框的文本 */

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
