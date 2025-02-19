#include "Submit.h"

void widget::Submit::ConnectSignal()
{
	_button.ClickedEvent().Subscribe(
		[this]()
		{
			try
			{
				_submit_event.Invoke(_line_edit.Text());
			}
			catch (std::exception const &e)
			{
			}
			catch (...)
			{
			}
		});

	_line_edit.TextChangedEvent().Subscribe(
		[this](QString const &text)
		{
			try
			{
				_submit_event.Invoke(_line_edit.Text());
			}
			catch (std::exception const &e)
			{
			}
			catch (...)
			{
			}
		});
}

widget::Submit::Submit()
{
	{
		setAutoFillBackground(true);
		QPalette temp_palette = palette();
		temp_palette.setColor(QPalette::Window, QColor{240, 240, 240});
		setPalette(temp_palette);
	}

	{
		// 将控件添加到布局中
		_layout.addWidget(&_line_edit);
		_layout.addWidget(&_button);

		// 控件之间的间距。在这里就是设置输入框和提交按钮之间的间距。
		_layout.setSpacing(10);

		// 布局内的内容区域与布局边框的间距。实际上相当于网页中的盒子内边距。
		_layout.setContentsMargins(0, 0, 0, 0);
	}

	ConnectSignal();
}

QString widget::Submit::PlaceholderText() const
{
	return _line_edit.PlaceholderText();
}

void widget::Submit::SetPlaceholderText(QString const &value)
{
	_line_edit.SetPlaceholderText(value);
}

QString widget::Submit::Text() const
{
	return _line_edit.Text();
}

void widget::Submit::SetText(QString const &value)
{
	_line_edit.SetText(value);
}

void widget::Submit::SetText(std::string const &value)
{
	SetText(QString{value.c_str()});
}

void widget::Submit::SetText(char const *value)
{
	SetText(QString{value});
}

QString widget::Submit::ButtonText() const
{
	return _button.text();
}

void widget::Submit::SetButtonText(QString const &value)
{
	_button.setText(value);
}

void widget::Submit::SetButtonText(std::string const &value)
{
	SetButtonText(QString{value.c_str()});
}

void widget::Submit::SetButtonText(char const *value)
{
	SetButtonText(QString{value});
}

base::IEvent<QString const &> &widget::Submit::SubmitEvent()
{
	return _submit_event;
}

void widget::Submit::HideSubmissionButton()
{
	_button.hide();
}

void widget::Submit::ShowSubmissionButton()
{
	_button.show();
}

bool widget::Submit::SubmissionButtonVisibility() const
{
	return !_button.isHidden();
}

void widget::Submit::SetSubmissionButtonVisibility(bool value)
{
	if (SubmissionButtonVisibility())
	{
		HideSubmissionButton();
	}
	else
	{
		ShowSubmissionButton();
	}
}
