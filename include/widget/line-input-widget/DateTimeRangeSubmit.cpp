#include "DateTimeRangeSubmit.h"
#include "base/string/define.h"
#include "qwindowdefs.h"
#include <iostream>

void widget::DateTimeRangeSubmit::ConnectSignal()
{
	connect(&_left_edit,
			&QDateTimeEdit::dateTimeChanged,
			[this](QDateTime const &date_time)
			{
				OnLeftDateTimeChanged();
			});

	connect(&_right_edit,
			&QDateTimeEdit::dateTimeChanged,
			[this](QDateTime const &date_time)
			{
				OnRightDateTimeChanged();
			});
}

/* #region 事件处理函数 */

void widget::DateTimeRangeSubmit::OnLeftDateTimeChanged()
{
	try
	{
		{
			// 检查非法输入
			bool error = false;
			if (LeftTimePoint() > RightTimePoint())
			{
				SetLeftInvalidInputStyle(true);
				SetRightInvalidInputStyle(true);
				error = true;
			}

			if (LeftTimePoint() < _min)
			{
				SetLeftInvalidInputStyle(true);
				error = true;
			}

			if (RightTimePoint() > _max)
			{
				SetRightInvalidInputStyle(true);
				error = true;
			}

			if (error)
			{
				return;
			}
		}

		{
			// 输入合法，开始处理
			SetLeftInvalidInputStyle(false);
			SetRightInvalidInputStyle(false);
			_submit_event.Invoke();
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << CODE_POS_STR << e.what() << std::endl;
	}
	catch (...)
	{
	}
}

void widget::DateTimeRangeSubmit::OnRightDateTimeChanged()
{
	try
	{
		{
			// 检查非法输入
			bool error = false;
			if (LeftTimePoint() > RightTimePoint())
			{
				SetLeftInvalidInputStyle(true);
				SetRightInvalidInputStyle(true);
				error = true;
			}

			if (LeftTimePoint() < _min)
			{
				SetLeftInvalidInputStyle(true);
				error = true;
			}

			if (RightTimePoint() > _max)
			{
				SetRightInvalidInputStyle(true);
				error = true;
			}

			if (error)
			{
				return;
			}
		}

		{
			// 输入合法，开始处理
			SetLeftInvalidInputStyle(false);
			SetRightInvalidInputStyle(false);
			_submit_event.Invoke();
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (...)
	{
	}
}

/* #endregion */

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
	}

	{
		setAutoFillBackground(true);
		QPalette temp_palette = palette();
		temp_palette.setColor(QPalette::Window, QColor{240, 240, 240});
		setPalette(temp_palette);
	}

	ConnectSignal();
}

widget::DateTimeRangeSubmit::DateTimeRangeSubmit(base::TimePointSinceEpoch const &min,
												 base::TimePointSinceEpoch const &max)
	: widget::DateTimeRangeSubmit()
{
	_min = min;
	_max = max;
}

base::IEvent<> &widget::DateTimeRangeSubmit::SubmitEvent()
{
	return _submit_event;
}

/* #region 日期时间数据 */

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

base::ClosedInterval<base::TimePointSinceEpoch> widget::DateTimeRangeSubmit::Interval() const
{
	return base::ClosedInterval<base::TimePointSinceEpoch>{LeftTimePoint(), RightTimePoint()};
}

/* #endregion */

/* #region 输入非法样式 */

void widget::DateTimeRangeSubmit::SetLeftInvalidInputStyle(bool is_invalid)
{
	if (is_invalid)
	{
		_left_edit.setStyleSheet("border: 2px solid red;");
	}
	else
	{
		// 恢复默认样式
		_left_edit.setStyleSheet("");
	}
}

void widget::DateTimeRangeSubmit::SetRightInvalidInputStyle(bool is_invalid)
{
	if (is_invalid)
	{
		_right_edit.setStyleSheet("border: 2px solid red;");
	}
	else
	{
		// 恢复默认样式
		_right_edit.setStyleSheet("");
	}
}

/* #endregion */
