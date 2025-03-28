#include "Button.h"
#include "widget/convert.h"

void widget::Button::ConnectSignal()
{
	connect(this,
			&QPushButton::clicked,
			[this]()
			{
				OnClicked();
			});

	connect(this,
			&QPushButton::pressed,
			[this]()
			{
				OnPressed();
			});

	connect(this,
			&QPushButton::released,
			[this]()
			{
				OnReleased();
			});
}

/* #region 事件处理函数 */

void widget::Button::enterEvent(QEnterEvent *event)
{
	_palette_before_enter_event = palette();

	QPushButton::enterEvent(event);
	QPalette temp_palette = palette();
	temp_palette.setColor(QPalette::Button, QColor{150, 190, 230});
	setPalette(temp_palette);

	try
	{
		_enter_event.Invoke();
	}
	catch (std::exception const &e)
	{
		std::cerr << CODE_POS_STR + e.what() << std::endl;
	}
	catch (...)
	{
	}
}

void widget::Button::leaveEvent(QEvent *event)
{
	QPushButton::leaveEvent(event);
	setPalette(_palette_before_enter_event);

	try
	{
		_leave_event.Invoke();
	}
	catch (std::exception const &e)
	{
		std::cerr << CODE_POS_STR + e.what() << std::endl;
	}
	catch (...)
	{
	}
}

void widget::Button::OnClicked()
{
	try
	{
		_clicked_event.Invoke();
	}
	catch (std::exception const &e)
	{
		std::cerr << CODE_POS_STR + e.what() << std::endl;
	}
	catch (...)
	{
	}
}

void widget::Button::OnPressed()
{
	_palette_before_pressed_event = palette();

	QPalette temp_palette = palette();
	temp_palette.setColor(QPalette::Button, QColor{100, 150, 255});
	setPalette(temp_palette);

	try
	{
		_pressed_event.Invoke();
	}
	catch (std::exception const &e)
	{
		std::cerr << CODE_POS_STR + e.what() << std::endl;
	}
	catch (...)
	{
	}
}

void widget::Button::OnReleased()
{
	setPalette(_palette_before_pressed_event);

	try
	{
		_released_event.Invoke();
	}
	catch (std::exception const &e)
	{
		std::cerr << CODE_POS_STR + e.what() << std::endl;
	}
	catch (...)
	{
	}
}

/* #endregion */

/* #region 构造函数 */

widget::Button::Button()
{
	SetText("按钮");
	setAutoFillBackground(true);

	// 按钮大小由内容决定，且固定大小。
	setSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);

	{
		QPalette temp_palette = palette();
		temp_palette.setColor(QPalette::Button, QColor{255, 255, 255});
		setPalette(temp_palette);
	}

	ConnectSignal();
}

widget::Button::Button(QString const &text)
	: Button()
{
	SetText(text);
}

widget::Button::Button(std::string const &text)
	: widget::Button(widget::ToQString(text))
{
}

widget::Button::Button(char const *text)
	: widget::Button(widget::ToQString(text))
{
}

/* #endregion */

/* #region 对外提供事件 */

base::IEvent<> &widget::Button::ClickedEvent()
{
	return _clicked_event;
}

base::IEvent<> &widget::Button::PressedEvent()
{
	return _pressed_event;
}

base::IEvent<> &widget::Button::ReleasedEvent()
{
	return _released_event;
}

base::IEvent<> &widget::Button::EnterEvent()
{
	return _enter_event;
}

base::IEvent<> &widget::Button::LeaveEvent()
{
	return _leave_event;
}

/* #endregion */

/* #region 文本 */

QString widget::Button::Text() const
{
	return text();
}

void widget::Button::SetText(QString const &value)
{
	setText(value);
}

void widget::Button::SetText(std::string const &value)
{
	SetText(QString{value.c_str()});
}

void widget::Button::SetText(char const *value)
{
	SetText(QString{value});
}

/* #endregion */
