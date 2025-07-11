#include "widget/CoreApplication.h"
#include "widget/FusionApplication.h"
#include "widget/io/Serial.h"
#include "widget/MainWindow.h"

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

	widget::Serial serial{"COM3"};

	serial.Start(base::serial::Direction::RX_TX,
				 base::serial::BaudRate{115200},
				 base::serial::DataBits{8},
				 base::serial::Parity::None,
				 base::serial::StopBits::One,
				 base::serial::HardwareFlowControl::None);

	return app.exec();
}

int main()
{
	return TestCoreApplication();
}
