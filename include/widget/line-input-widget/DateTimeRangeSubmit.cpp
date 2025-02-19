#include "DateTimeRangeSubmit.h"
#include "base/time/TimePointSinceEpoch.h"
#include "qwindowdefs.h"
#include "widget/Button.h"
#include <chrono>
#include <exception>
#include <iostream>

widget::DateTimeRangeSubmit::DateTimeRangeSubmit()
{
	{
		_left_edit.setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);

		// 设置当前日期和时间
		_left_edit.setDateTime(QDateTime::currentDateTime());

		// 设置显示格式
		_left_edit.setDisplayFormat("yyyy-MM-dd hh:mm:ss");
	}

	{
		_right_edit.setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);

		// 设置当前日期和时间
		_right_edit.setDateTime(QDateTime::currentDateTime());

		// 设置显示格式
		_right_edit.setDisplayFormat("yyyy-MM-dd hh:mm:ss");
	}

	{
		_layout.AddWidget(&_left_edit);
		_layout.AddWidget(&_label);
		_layout.AddWidget(&_right_edit);
		_layout.AddWidget(&_button);
	}

	{
		setAutoFillBackground(true);
		QPalette temp_palette = palette();
		temp_palette.setColor(QPalette::Window, QColor{240, 240, 240});
		setPalette(temp_palette);
	}

	{
		// 连接信号
		connect(&_button,
				&widget::Button::clicked,
				[this]()
				{
					try
					{
						_submit_event.Invoke();
					}
					catch (std::exception const &e)
					{
						std::cerr << e.what() << std::endl;
					}
					catch (...)
					{
					}
				});
	}
}

base::IEvent<> &widget::DateTimeRangeSubmit::SubmitEvent()
{
	return _submit_event;
}

base::TimePointSinceEpoch widget::DateTimeRangeSubmit::LeftTimePoint() const
{
	QDateTime selectedDateTime = _left_edit.dateTime();
	return base::TimePointSinceEpoch{std::chrono::seconds{selectedDateTime.toSecsSinceEpoch()}};
}

base::TimePointSinceEpoch widget::DateTimeRangeSubmit::RightTimePoint() const
{
	QDateTime selectedDateTime = _right_edit.dateTime();
	return base::TimePointSinceEpoch{std::chrono::seconds{selectedDateTime.toSecsSinceEpoch()}};
}
