#include "RangeSubmit.h"
#include <climits>
#include <iostream>
#include <widget/Conversion.h>

widget::RangeSubmit::RangeSubmit()
{
	{
		_left_edit.setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
		_right_edit.setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);

		_left_edit.setValidator(&_validator);
		_right_edit.setValidator(&_validator);
	}

	{
		_layout.addWidget(&_left_edit);
		_layout.addWidget(&_label);
		_layout.addWidget(&_right_edit);
		_layout.addWidget(&_button);

		// 控件之间的间距。
		_layout.setSpacing(10);

		// 布局内的内容区域与布局边框的间距。实际上相当于网页中的盒子内边距。
		_layout.setContentsMargins(0, 0, 0, 0);
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

QString widget::RangeSubmit::LeftText() const
{
	return _left_edit.text();
}

std::string widget::RangeSubmit::LeftTextStdString() const
{
	std::string ret;
	ret << LeftText();
	return ret;
}

QString widget::RangeSubmit::RightText() const
{
	return _right_edit.text();
}

std::string widget::RangeSubmit::RightTextStdString() const
{
	std::string ret;
	ret << RightText();
	return ret;
}

base::IEvent<> &widget::RangeSubmit::SubmitEvent()
{
	return _submit_event;
}
