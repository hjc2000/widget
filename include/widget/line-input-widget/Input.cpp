#include "Input.h"
#include "widget/Conversion.h"

void widget::Input::ConnectSignal()
{
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
					_text_editing_finished_event.Invoke(_line_edit.text());
				}
				catch (std::exception const &e)
				{
				}
				catch (...)
				{
				}

				try
				{
					_text_changing_finished_event.Invoke(_line_edit.text());
				}
				catch (std::exception const &e)
				{
				}
				catch (...)
				{
				}
			});
}

widget::Input::Input()
{
	_line_edit.setPlaceholderText("在此处输入内容...");
	_line_edit.setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
	_layout.AddWidget(&_line_edit);
	ConnectSignal();
}

/* #region PlaceholderText */

QString widget::Input::PlaceholderText() const
{
	return _line_edit.placeholderText();
}

void widget::Input::SetPlaceholderText(QString const &value)
{
	_line_edit.setPlaceholderText(value);
}

void widget::Input::SetPlaceholderText(std::string const &value)
{
	SetPlaceholderText(QString{value.c_str()});
}

void widget::Input::SetPlaceholderText(char const *value)
{
	SetPlaceholderText(QString{value});
}

std::string widget::Input::PlaceholderTextStdString() const
{
	std::string ret = std::to_string(PlaceholderText());
	return ret;
}

/* #endregion */

/* #region Text */

QString widget::Input::Text() const
{
	return _line_edit.text();
}

void widget::Input::SetText(QString const &value)
{
	_line_edit.setText(value);

	try
	{
		_text_changing_finished_event.Invoke(_line_edit.text());
	}
	catch (std::exception const &e)
	{
	}
	catch (...)
	{
	}
}

void widget::Input::SetText(std::string const &value)
{
	SetText(QString{value.c_str()});
}

void widget::Input::SetText(char const *value)
{
	SetText(QString{value});
}

std::string widget::Input::TextStdString() const
{
	std::string ret = std::to_string(Text());
	return ret;
}

/* #endregion */

/* #region 对外提供事件 */

base::IEvent<QString const &> &widget::Input::TextChangedEvent()
{
	return _text_changed_event;
}

base::IEvent<QString const &> &widget::Input::TextChangingFinishedEvent()
{
	return _text_changing_finished_event;
}

base::IEvent<QString const &> &widget::Input::TextEditedEvent()
{
	return _text_edited_event;
}

base::IEvent<QString const &> &widget::Input::TextEditingFinishedEvent()
{
	return _text_editing_finished_event;
}

/* #endregion */

void widget::Input::SetInvalidInputStyle(bool is_invalid)
{
	if (is_invalid)
	{
		_line_edit.setStyleSheet("border: 2px solid red;");
	}
	else
	{
		// 恢复默认样式
		_line_edit.setStyleSheet("");
	}
}
