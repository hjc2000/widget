#pragma once
#include <base/delegate/Delegate.h>
#include <QDateTimeEdit>
#include <QHBoxLayout>
#include <widget/Button.h>

namespace widget
{
	class DateTimeRangeSubmit :
		QWidget
	{
	private:
		QHBoxLayout _layout{this};
		QDateTimeEdit _left_edit{};
		QDateTimeEdit _right_edit{};

	public:
	};
} // namespace widget