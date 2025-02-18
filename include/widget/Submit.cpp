#include "Submit.h"

void widget::Submit::InitializeLayout()
{
	// 将控件添加到布局中
	_layout.addWidget(&_line_edit);
	_layout.addWidget(&_button);

	// 控件之间的间距。在这里就是设置输入框和提交按钮之间的间距。
	_layout.setSpacing(10);

	// 布局内的内容区域与布局边框的间距。实际上相当于网页中的盒子内边距。
	_layout.setContentsMargins(0, 0, 0, 0);
}

void widget::Submit::ConnectSignal()
{
	_button.ClickedEvent().Subscribe(
		[this]()
		{
			try
			{
				_submit_event.Invoke(_line_edit.text());
			}
			catch (std::exception const &e)
			{
			}
			catch (...)
			{
			}
		});

	connect(&_line_edit,
			&QLineEdit::returnPressed,
			[this]()
			{
				try
				{
					_submit_event.Invoke(_line_edit.text());
				}
				catch (std::exception const &e)
				{
				}
				catch (...)
				{
				}
			});

	connect(&_line_edit,
			&QLineEdit::textChanged,
			[this]()
			{
				try
				{
					_text_changed_event.Invoke(_line_edit.text());
				}
				catch (std::exception const &e)
				{
				}
				catch (...)
				{
				}
			});

	connect(&_line_edit,
			&QLineEdit::textEdited,
			[this]()
			{
				try
				{
					_text_edited_event.Invoke(_line_edit.text());
				}
				catch (std::exception const &e)
				{
				}
				catch (...)
				{
				}
			});

	connect(&_line_edit,
			&QLineEdit::editingFinished,
			[this]()
			{
				try
				{
					_editing_finished.Invoke(_line_edit.text());
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
	_line_edit.setPlaceholderText("在此处输入内容...");

	// 输入框自适应缩放
	_line_edit.setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);

	// 按钮大小由内容决定
	_button.setSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);

	{
		setAutoFillBackground(true);
		QPalette temp_palette = palette();
		temp_palette.setColor(QPalette::Window, QColor{255, 255, 255});
		setPalette(temp_palette);
	}

	InitializeLayout();
	ConnectSignal();
}

QString widget::Submit::PlaceholderText() const
{
	return _line_edit.placeholderText();
}

void widget::Submit::SetPlaceholderText(QString const &value)
{
	_line_edit.setPlaceholderText(value);
}

QString widget::Submit::Text() const
{
	return _line_edit.text();
}

void widget::Submit::SetText(QString const &value)
{
	_line_edit.setText(value);
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

base::IEvent<QString const &> &widget::Submit::TextChangedEvent()
{
	return _text_changed_event;
}

base::IEvent<QString const &> &widget::Submit::TextEditedEvent()
{
	return _text_edited_event;
}

base::IEvent<QString const &> &widget::Submit::EditingFinishedEvent()
{
	return _editing_finished;
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
