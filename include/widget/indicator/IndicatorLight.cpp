#include "IndicatorLight.h"

void widget::IndicatorLight::paintEvent(QPaintEvent *event)
{
	QPainter painter{this};

	// 开启抗锯齿
	painter.setRenderHint(QPainter::Antialiasing);

	QColor color = CurrentColor();
	painter.setBrush(color);

	int border_width = 1;
	QPen pen{Qt::GlobalColor::black};
	pen.setWidth(border_width);
	painter.setPen(pen);

	// 调整绘图区域，避免边线超出控件范围。
	// 根据边线宽度调整
	//
	// 如果边线宽度不为 0，绘制边线一定会超出控件范围，导致虽然绘制的是圆形，看着是矩形。
	// 因为控件的视图窗口是矩形，超出范围的边线就看不见了，导致边线外围好像被用一个矩形
	// 模具切割。
	QRect adjustedRect = rect().adjusted(border_width, border_width, -border_width, -border_width);

	// 绘制圆形
	painter.drawEllipse(adjustedRect);
}

void widget::IndicatorLight::TurnOn()
{
	if (_state == base::led::State::On)
	{
		return;
	}

	_state = base::led::State::On;
	update();
}

void widget::IndicatorLight::TurnOff()
{
	if (_state == base::led::State::Off)
	{
		return;
	}

	_state = base::led::State::Off;
	update();
}
