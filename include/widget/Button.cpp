#include "Button.h"

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
				try
				{
					_pressed_event.Invoke();
				}
				catch (...)
				{
				}
			});
}

#pragma endregion

widget::Button::Button(QWidget *parent)
	: QPushButton(parent)
{
	SetText("按钮");

	// 设置按钮的样式表
	setStyleSheet("QPushButton {"
				  "   background-color: white;"
				  "   color: black;"
				  "}"
				  "QPushButton:pressed {"
				  "   background-color: lightgray;"
				  "}"
				  "QPushButton:hover {"
				  "   background-color: lightblue;"
				  "}");

	ConnectSignal();
}

widget::Button::Button(QWidget *parent, QString const &text)
	: Button(parent)
{
	SetText(text);
}

#pragma region 事件

base::IEvent<> &widget::Button::ClickedEvent()
{
	return _clicked_event;
}

base::IEvent<> &widget::Button::PressedEvent()
{
	return _pressed_event;
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
