#include "IntRangeSubmit.h"

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
