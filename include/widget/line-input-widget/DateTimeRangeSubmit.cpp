#include "DateTimeRangeSubmit.h" // IWYU pragma: keep
#include "base/string/define.h"
#include <iostream>

void widget::DateTimeRangeSubmit::ConnectSignal()
{
	{
		QMetaObject::Connection connection =
			connect(_left_edit.get(),
					&QDateTimeEdit::dateTimeChanged,
					[this](QDateTime const &date_time)
					{
						OnLeftDateTimeChanged();
					});

		_connections.push_back(connection);
	}

	{
		QMetaObject::Connection connection =
			connect(_right_edit.get(),
					&QDateTimeEdit::dateTimeChanged,
					[this](QDateTime const &date_time)
					{
						OnRightDateTimeChanged();
					});

		_connections.push_back(connection);
	}
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

widget::DateTimeRangeSubmit::DateTimeRangeSubmit()
{
	{
		_left_edit->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);

		// 设置当前日期和时间
		_left_edit->setDateTime(QDateTime::currentDateTime());

		// 设置显示格式
		_left_edit->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
	}

	{
		_right_edit->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);

		// 设置当前日期和时间
		_right_edit->setDateTime(QDateTime::currentDateTime());

		// 设置显示格式
		_right_edit->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
	}

	{
		_layout.AddWidget(_left_edit);
		_layout.AddWidget(_label);
		_layout.AddWidget(_right_edit);
	}

	{
		setAutoFillBackground(true);
		QPalette temp_palette = palette();
		temp_palette.setColor(QPalette::Window, QColor{240, 240, 240});
		setPalette(temp_palette);
	}

	ConnectSignal();
}
