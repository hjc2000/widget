#pragma once
#include <base/delegate/Delegate.h>
#include <QDateTimeEdit>
#include <QHBoxLayout>
#include <QLabel>
#include <widget/Button.h>

namespace widget
{
	/// @brief 日期时间范围提交控件。
	class DateTimeRangeSubmit :
		public QWidget
	{
	private:
		QHBoxLayout _layout{this};
		QDateTimeEdit _left_edit{};
		QDateTimeEdit _right_edit{};
		QLabel _label{"-"};
		widget::Button _button{"提交"};

	public:
		DateTimeRangeSubmit();
	};
} // namespace widget