#include "RangeSubmit.h"
#include "widget/Conversion.h"
#include <climits>

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
		_left_edit.TextChangingFinishedEvent().Subscribe([this](QString const &text)
														 {
															 _submit_event.Invoke();
														 });

		_right_edit.TextChangingFinishedEvent().Subscribe([this](QString const &text)
														  {
															  _submit_event.Invoke();
														  });
	}
}

/* #region PlaceholderText */

QString widget::RangeSubmit::LeftPlaceholderText() const
{
	return _left_edit.PlaceholderText();
}

void widget::RangeSubmit::SetLeftPlaceholderText(QString const &value)
{
	_left_edit.SetPlaceholderText(value);
}

void widget::RangeSubmit::SetLeftPlaceholderText(std::string const &value)
{
	_left_edit.SetPlaceholderText(value.c_str());
}

void widget::RangeSubmit::SetLeftPlaceholderText(char const *value)
{
	_left_edit.SetPlaceholderText(value);
}

std::string widget::RangeSubmit::LeftPlaceholderTextStdString() const
{
	return std::to_string(LeftPlaceholderText());
}

QString widget::RangeSubmit::RightPlaceholderText() const
{
	return _right_edit.PlaceholderText();
}

void widget::RangeSubmit::SetRightPlaceholderText(QString const &value)
{
	_right_edit.SetPlaceholderText(value);
}

void widget::RangeSubmit::SetRightPlaceholderText(std::string const &value)
{
	_right_edit.SetPlaceholderText(value.c_str());
}

void widget::RangeSubmit::SetRightPlaceholderText(char const *value)
{
	_right_edit.SetPlaceholderText(value);
}

std::string widget::RangeSubmit::RightPlaceholderTextStdString() const
{
	return std::to_string(RightPlaceholderText());
}

/* #endregion */

/* #region 输入框的文本 */

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
	return std::to_string(LeftText());
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
	return std::to_string(RightText());
}

/* #endregion */

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
