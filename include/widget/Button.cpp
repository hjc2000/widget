#include "Button.h"
#include <QPainter>
#include <QPaintEvent>

#pragma region 初始化方法

void widget::Button::ConnectSignal()
{
	connect(this,
			&QPushButton::clicked,
			[this]()
			{
				try
				{
					_clicked_event.Invoke();
				}
				catch (...)
				{
				}
			});

	connect(this,
			&QPushButton::pressed,
			[this]()
			{
				_palette_before_pressed_event = palette();

				QPalette temp_palette = palette();
				temp_palette.setColor(QPalette::Button, QColor{100, 150, 255});
				setPalette(temp_palette);

				try
				{
					_pressed_event.Invoke();
				}
				catch (...)
				{
				}
			});

	connect(this,
			&QPushButton::released,
			[this]()
			{
				setPalette(_palette_before_pressed_event);

				try
				{
					_released_event.Invoke();
				}
				catch (...)
				{
				}
			});
}

#pragma endregion

#pragma region 重写事件

void widget::Button::paintEvent(QPaintEvent *event)
{
	QPushButton::paintEvent(event);
	QPainter painter{this};
	painter.setPen(QPen{Qt::black, 0.5});
	painter.drawRect(rect().adjusted(0, 0, -1, -1));
}

void widget::Button::enterEvent(QEnterEvent *event)
{
	_palette_before_enter_event = palette();

	QPushButton::enterEvent(event);
	QPalette temp_palette = palette();
	temp_palette.setColor(QPalette::Button, QColor{204, 232, 255});
	setPalette(temp_palette);

	try
	{
		_enter_event.Invoke();
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
	catch (...)
	{
	}
}

#pragma endregion

#pragma region 构造函数

widget::Button::Button(QWidget *parent)
	: QPushButton(parent)
{
	SetText("按钮");
	setAutoFillBackground(true);

	_origin_palette = palette();
	_origin_palette.setColor(QPalette::Button, QColor{255, 255, 255});
	setPalette(_origin_palette);

	ConnectSignal();
}

widget::Button::Button(QWidget *parent, QString const &text)
	: Button(parent)
{
	SetText(text);
}

#pragma endregion

#pragma region 事件

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

#pragma endregion

#pragma region 按钮文本

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

#pragma endregion
