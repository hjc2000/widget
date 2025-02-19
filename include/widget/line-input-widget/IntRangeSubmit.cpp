#include "IntRangeSubmit.h"
#include <base/string/define.h>
#include <base/string/Parse.h>
#include <cstdint>
#include <exception>
#include <iostream>
#include <stdexcept>

namespace widget
{
	int64_t IntRangeSubmit::ParseLeftValue() const
	{
		int64_t value = base::ParseInt64(_range_submit.LeftTextStdString());
		return value;
	}

	int64_t IntRangeSubmit::ParseRightValue() const
	{
		int64_t value = base::ParseInt64(_range_submit.RightTextStdString());
		return value;
	}

	void IntRangeSubmit::OnSubmit()
	{
		try
		{
			int64_t left_value = ParseLeftValue();
			int64_t right_value = ParseRightValue();
			if (left_value > right_value)
			{
				std::cerr << CODE_POS_STR + "左侧值不能大于右侧值。" << std::endl;
				return;
			}

			if (left_value < _min)
			{
				std::cerr << CODE_POS_STR + "左侧值不能小于最小值。" << std::endl;
				return;
			}

			if (right_value > _max)
			{
				std::cerr << CODE_POS_STR + "右侧值不能大于最大值。" << std::endl;
				return;
			}

			// 数据合法，应用输入。
			_left_value = left_value;
			_right_value = right_value;

			std::cout << "数据合法，应用输入。"
					  << "左侧值：" << _left_value
					  << "右侧值：" << _right_value
					  << std::endl;

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
} // namespace widget

namespace widget
{
	IntRangeSubmit::IntRangeSubmit(int64_t min, int64_t max)
	{
		_min = min;
		_max = max;
		if (_min > _max)
		{
			throw std::invalid_argument{CODE_POS_STR + "最小值不能大于最大值。"};
		}

		{
			_layout.addWidget(&_range_submit);

			// 控件之间的间距。
			_layout.setSpacing(10);

			// 布局内的内容区域与布局边框的间距。实际上相当于网页中的盒子内边距。
			_layout.setContentsMargins(0, 0, 0, 0);
		}

		_range_submit.SubmitEvent().Subscribe(
			[this]()
			{
				OnSubmit();
			});
	}
} // namespace widget

namespace widget
{
	int64_t IntRangeSubmit::MinValue() const
	{
		return _min;
	}

	void IntRangeSubmit::SetMinValue(int64_t value)
	{
		_min = value;
	}

	int64_t IntRangeSubmit::MaxValue() const
	{
		return _max;
	}

	void IntRangeSubmit::SetMaxValue(int64_t value)
	{
		_max = value;
	}
} // namespace widget

namespace widget
{
	int64_t IntRangeSubmit::LeftValue() const
	{
		return _left_value;
	}

	int64_t IntRangeSubmit::RightValue() const
	{
		return _right_value;
	}
} // namespace widget

namespace widget
{
	base::IEvent<> &IntRangeSubmit::SubmitEvent()
	{
		return _submit_event;
	}
} // namespace widget
