#include "RangeSubmit.h"
#include <climits>
#include <widget/Conversion.h>

widget::RangeSubmit::RangeSubmit()
{
	setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);

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

	{
		// 订阅事件
		_left_edit.TextEditingFinishedEvent().Subscribe(
			[this](QString const &text)
			{
				_submit_event.Invoke();
			});

		_right_edit.TextEditingFinishedEvent().Subscribe(
			[this](QString const &text)
			{
				_submit_event.Invoke();
			});
	}
}

QString widget::RangeSubmit::LeftText() const
{
	return _left_edit.Text();
}

void widget::RangeSubmit::SetLeftText(QString const &value)
{
	_left_edit.SetText(value);
}

void widget::RangeSubmit::SetLeftText(std::string const &value)
{
	_left_edit.SetText(value);
}

void widget::RangeSubmit::SetLeftText(char const *value)
{
	_left_edit.SetText(value);
}

std::string widget::RangeSubmit::LeftTextStdString() const
{
	return widget::ToString(LeftText());
}

QString widget::RangeSubmit::RightText() const
{
	return _right_edit.Text();
}

void widget::RangeSubmit::SetRightText(QString const &value)
{
	_right_edit.SetText(value);
}

void widget::RangeSubmit::SetRightText(std::string const &value)
{
	_right_edit.SetText(value);
}

void widget::RangeSubmit::SetRightText(char const *value)
{
	_right_edit.SetText(value);
}

std::string widget::RangeSubmit::RightTextStdString() const
{
	return widget::ToString(RightText());
}

base::IEvent<> &widget::RangeSubmit::SubmitEvent()
{
	return _submit_event;
}

void widget::RangeSubmit::SetLeftInvalidInputStyle(bool is_invalid)
{
	_left_edit.SetInvalidInputStyle(is_invalid);
}

void widget::RangeSubmit::SetRightInvalidInputStyle(bool is_invalid)
{
	_right_edit.SetInvalidInputStyle(is_invalid);
}
