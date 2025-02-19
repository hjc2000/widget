#include "RangeSubmit.h"
#include "widget/Conversion.h"
#include <climits>
#include <widget/Conversion.h>

widget::RangeSubmit::RangeSubmit()
{
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

	_button.ClickedEvent().Subscribe(
		[this]()
		{
			_submit_event.Invoke();
		});
}

QString widget::RangeSubmit::LeftText() const
{
	return _left_edit.Text();
}

std::string widget::RangeSubmit::LeftTextStdString() const
{
	return widget::ToString(LeftText());
}

QString widget::RangeSubmit::RightText() const
{
	return _right_edit.Text();
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
