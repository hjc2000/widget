#include "base/embedded/serial/Serial.h"
#include "base/embedded/serial/serial_handle.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Span.h"
#include "base/task/delay.h"
#include "base/task/task.h"
#include "widget/CoreApplication.h"
#include "widget/FusionApplication.h"
#include "widget/MainWindow.h"
#include <chrono>
#include <cstdint>
#include <iostream>
#include <string>

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

	auto serials = base::serial::scan_serials_for_details();
	for (auto const &serial : serials)
	{
		std::cout << serial.Name() << std::endl;
		std::cout << serial.Description() << std::endl;
	}

	base::serial::Serial serial{"COM3"};

	serial.Start(base::serial::Direction::RX_TX,
				 base::serial::BaudRate{115200},
				 base::serial::DataBits{8},
				 base::serial::Parity::None,
				 base::serial::StopBits::One,
				 base::serial::HardwareFlowControl::None);

	base::task::run(
		[&]()
		{
			uint8_t buffer[1024]{};
			std::string str{"6666666666\n"};

			while (true)
			{
				int32_t have_read = serial.Read(base::Span{buffer, sizeof(buffer)});
				std::cout.write(reinterpret_cast<char const *>(buffer), have_read);
			}
		});

	base::task::run(
		[&]()
		{
			std::string str{"6666666666\n"};

			while (true)
			{
				base::ReadOnlySpan span{
					reinterpret_cast<uint8_t const *>(str.c_str()),
					static_cast<int32_t>(str.size()),
				};

				serial.Write(span);
				base::task::Delay(std::chrono::milliseconds{1000});
			}
		});

	return app.exec();
}

int main()
{
	return TestCoreApplication();
}
