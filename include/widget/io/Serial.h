#pragma once
#include "base/embedded/serial/serial_parameter.h"
#include "qserialport.h"
#include "serial_handle.h"
#include "widget/thread/Thread.h"
#include <iostream>
#include <memory>
#include <string>

namespace widget
{
	class Serial :
		public base::serial::serial_handle
	{
	private:
		widget::Thread _thread{};
		std::weak_ptr<QSerialPort> _serial{};

		void OnReceiveData()
		{
			std::shared_ptr<QSerialPort> serial = _serial.lock();
			if (serial == nullptr)
			{
				return;
			}

			QByteArray receive_data = serial->readAll();
			std::cout.write(receive_data.data(), receive_data.size());
		}

	public:
		Serial(std::string const &name)
		{
			_thread.start();

			std::shared_ptr<base::task::ITask> task = _thread.InvokeAsync(
				[this]()
				{
					std::shared_ptr<QSerialPort> serial{new QSerialPort{}};
					_thread.AddResource(serial);
					_serial = serial;

					// 这里的 lambda 表达式千万不能按值捕获 std::shared_ptr<QSerialPort> serial,
					// 因为 lambda 表达式会被储存在 serial 中，进而导致循环引用。
					QSerialPort::connect(serial.get(),
										 &QSerialPort::readyRead,
										 [this]()
										 {
											 OnReceiveData();
										 });
				});

			task->Wait();
		}

		~Serial()
		{
			_thread.Dispose();
		}

		virtual void Start(base::serial::Direction direction,
						   base::serial::BaudRate const &baud_rate,
						   base::serial::DataBits const &data_bits,
						   base::serial::Parity parity,
						   base::serial::StopBits stop_bits,
						   base::serial::HardwareFlowControl hardware_flow_control) override
		{
		}

		virtual int32_t Read(base::Span const &span) override
		{
			return 0;
		}

		virtual void Write(base::ReadOnlySpan const &span) override
		{
		}

		virtual void Flush() override
		{
		}
	};

} // namespace widget
