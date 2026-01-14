#include "IntRangeSubmit.h" // IWYU pragma: keep
#include "base/string/Parse.h"
#include <cstdint>

bool widget::IntRangeSubmit::TryParseLeftValue(int64_t &out)
{
	try
	{
		out = base::Parse<int64_t>(_range_submit->LeftTextStdString());
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
		out = base::Parse<int64_t>(_range_submit->RightTextStdString());
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
