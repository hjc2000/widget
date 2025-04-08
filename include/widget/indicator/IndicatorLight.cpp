#include "IndicatorLight.h"
#include "base/enum.h"
#include "base/math/Size.h"
#include "qcolor.h"
#include "qnamespace.h"
#include "qpainter.h"

void widget::IndicatorLight::paintEvent(QPaintEvent *event)
{
	QPainter painter{this};
	QColor color = CurrentColor();
	painter.setBrush(color);

	QPen pen{Qt::GlobalColor::white};
	pen.setWidth(3);
	painter.setPen(pen);

	// 绘制圆形
	painter.drawEllipse(rect());
}

widget::IndicatorLight::IndicatorLight()
	: IndicatorLight(base::Size{20, 20},
					 Qt::GlobalColor::green,
					 Qt::GlobalColor::gray)
{
}

widget::IndicatorLight::IndicatorLight(base::Size const &size, QColor on_color, QColor off_color)
	: IndicatorLight(size,
					 base::Enum::SwitchState::Off,
					 on_color,
					 off_color)
{
}

widget::IndicatorLight::IndicatorLight(base::Size const &size,
									   base::Enum::SwitchState initial_state,
									   QColor on_color,
									   QColor off_color)
{
	setFixedSize(size.XSize(), size.YSize());
	_state = initial_state;
	_on_color = on_color;
	_off_color = off_color;
}

base::Enum::SwitchState widget::IndicatorLight::State() const
{
	return _state;
}

void widget::IndicatorLight::SetState(base::Enum::SwitchState value)
{
	if (_state == value)
	{
		return;
	}

	_state = value;

	// 触发重绘
	update();
}

QColor widget::IndicatorLight::OnColor() const
{
	return _on_color;
}

void widget::IndicatorLight::SetOnColor(QColor value)
{
	if (_on_color == value)
	{
		return;
	}

	_on_color = value;

	// 触发重绘
	update();
}

QColor widget::IndicatorLight::OffColor() const
{
	return _off_color;
}

void widget::IndicatorLight::SetOffColor(QColor value)
{
	if (_off_color == value)
	{
		return;
	}

	_off_color = value;

	// 触发重绘
	update();
}

QColor widget::IndicatorLight::CurrentColor() const
{
	if (_state == base::Enum::SwitchState::Off)
	{
		return _off_color;
	}

	return _on_color;
}
