#include "base/stream/Span.h"
#include "base/task/task.h"
#include "widget/CoreApplication.h"
#include "widget/FusionApplication.h"
#include "widget/io/Serial.h"
#include "widget/MainWindow.h"
#include <cstdint>
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

	base::task::run(
		[&]()
		{
			widget::Serial serial{"COM3"};

			serial.Start(base::serial::Direction::RX_TX,
						 base::serial::BaudRate{115200},
						 base::serial::DataBits{8},
						 base::serial::Parity::None,
						 base::serial::StopBits::One,
						 base::serial::HardwareFlowControl::None);

			uint8_t buffer[1024]{};

			while (true)
			{
				int32_t have_read = serial.Read(base::Span{buffer, sizeof(buffer)});
				std::cout.write(reinterpret_cast<char const *>(buffer), have_read);
			}
		});

	return app.exec();
}

int main()
{
	return TestCoreApplication();
}
