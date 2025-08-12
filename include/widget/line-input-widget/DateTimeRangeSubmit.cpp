#include "DateTimeRangeSubmit.h" // IWYU pragma: keep
#include "base/string/define.h"
#include <iostream>

void widget::DateTimeRangeSubmit::ConnectSignal()
{
	QMetaObject::Connection connection;

	connection = connect(&_left_edit,
						 &QDateTimeEdit::dateTimeChanged,
						 [this](QDateTime const &date_time)
						 {
							 OnLeftDateTimeChanged();
						 });

	_connections.push_back(connection);

	connection = connect(&_right_edit,
						 &QDateTimeEdit::dateTimeChanged,
						 [this](QDateTime const &date_time)
						 {
							 OnRightDateTimeChanged();
						 });

	_connections.push_back(connection);
}

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
