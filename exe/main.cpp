#include "base/embedded/serial/Serial.h"
#include "base/embedded/serial/serial_handle.h"
#include "base/embedded/serial/SoftWareTimeoutSerial.h"
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
#include <memory>
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

	std::shared_ptr<base::serial::SoftWareTimeoutSerial> soft_serial{new base::serial::SoftWareTimeoutSerial{
		std::shared_ptr<base::serial::Serial>{new base::serial::Serial{"COM3"}},
		1024 * 10,
		20,
	}};

	soft_serial->Start(base::serial::Direction::RX_TX,
					   base::serial::BaudRate{115200},
					   base::serial::DataBits{8},
					   base::serial::Parity::None,
					   base::serial::StopBits::One,
					   base::serial::HardwareFlowControl::None);

	base::task::run(
		[&]()
		{
			uint8_t buffer[1024]{};
			int64_t count = 0;

			while (true)
			{
				int32_t have_read = soft_serial->Read(base::Span{buffer, sizeof(buffer)});
				if (have_read == 0)
				{
					std::cout << "Read 函数返回 0, 流结束。读线程退出。" << std::endl;
					return;
				}

				std::cout.write(reinterpret_cast<char const *>(buffer), have_read);

				count++;
				if (count > 10)
				{
					soft_serial->Close();
				}
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

				soft_serial->Write(span);
				base::task::Delay(std::chrono::milliseconds{1000});
			}
		});

	return app.exec();
}

int main()
{
	return TestCoreApplication();
}
