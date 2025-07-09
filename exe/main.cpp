#include "qserialport.h"
#include "widget/CoreApplication.h"
#include "widget/FusionApplication.h"
#include "widget/MainWindow.h"
#include <iostream>

int TestFusionApplication()
{
	widget::FusionApplication app{};
	widget::MainWindow window{};
	window.showMaximized();
	return app.exec();
}

int TestCoreApplication()
{
	widget::CoreApplication app{};
	QSerialPort serial{};
	serial.setPortName("COM4");
	serial.setBaudRate(115200);

	// 设置数据位
	serial.setDataBits(QSerialPort::DataBits::Data8);

	// 设置校验位
	serial.setParity(QSerialPort::Parity::NoParity);

	// 设置停止位
	serial.setStopBits(QSerialPort::StopBits::OneStop);

	// 设置流控制
	serial.setFlowControl(QSerialPort::FlowControl::NoFlowControl);

	serial.open(QIODeviceBase::OpenModeFlag::ReadWrite);

	QSerialPort::connect(&serial,
						 &QSerialPort::readyRead,
						 [&]()
						 {
							 QByteArray receive_data = serial.readAll();
							 std::cout.write(receive_data.data(), receive_data.size());
						 });

	return app.exec();
}

int main()
{
	return TestCoreApplication();
}
