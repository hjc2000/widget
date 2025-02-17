#include "test_qwt.h"
#include <QMainWindow>
#include <QPen>
#include <qwt-qt6/qwt_plot.h>
#include <qwt-qt6/qwt_plot_curve.h>
#include <qwt-qt6/qwt_symbol.h>
#include <widget/FusionApplication.h>

void widget::test_qwt()
{
	int argc = 1;

	char *argv[] = {
		const_cast<char *>("Hello World"),
		nullptr,
	};

	widget::FusionApplication app{argc, argv};
	QWidget widget{};

	// 创建 QwtPlot 对象
	QwtPlot plot{&widget};
	plot.setTitle("y = x Curve Example");
	plot.setAxisTitle(QwtPlot::xBottom, "X Axis");
	plot.setAxisTitle(QwtPlot::yLeft, "Y Axis");

	// 创建 QwtPlotCurve 对象
	QwtPlotCurve curve;
	curve.setTitle("y = x");

	// 设置符号（可选）
	QwtSymbol symbol(QwtSymbol::Ellipse, Qt::NoBrush, QPen(Qt::red), QSize(5, 5));
	curve.setSymbol(&symbol);

	// 准备数据
	QVector<double> xData, yData;
	for (double x = -10.0; x <= 10.0; x += 0.1)
	{
		xData.append(x);
		yData.append(x); // y = x
	}

	// 将数据附加到曲线
	curve.setSamples(xData, yData);

	// 将曲线附加到绘图
	curve.attach(&plot);

	// 调整轴范围
	plot.setAxisScale(QwtPlot::xBottom, -10.0, 10.0);
	plot.setAxisScale(QwtPlot::yLeft, -10.0, 10.0);

	// 显示绘图
	plot.replot();
	widget.showMaximized();
	app.exec();
}
