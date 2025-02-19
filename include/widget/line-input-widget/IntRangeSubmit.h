#pragma once
#include "base/delegate/IEvent.h"
#include "qboxlayout.h"
#include "RangeSubmit.h"
#include <cstdint>

namespace widget
{
	class IntRangeSubmit :
		public QWidget
	{
	private:
		QHBoxLayout _layout = QHBoxLayout{this};
		widget::RangeSubmit _range_submit{};

	private:
		int64_t _min = INT64_MIN;
		int64_t _max = INT64_MAX;

		int64_t _left_value = 0;
		int64_t _right_value = 0;
		int64_t ParseLeftValue() const;
		int64_t ParseRightValue() const;
		void OnSubmit();

	private:
		base::Delegate<> _submit_event;

	public:
		IntRangeSubmit(int64_t min, int64_t max);

		int64_t MinValue() const;
		void SetMinValue(int64_t value);
		int64_t MaxValue() const;
		void SetMaxValue(int64_t value);

	public:
		int64_t LeftValue() const;
		int64_t RightValue() const;

	public:
		base::IEvent<> &SubmitEvent();
	};
} // namespace widget
