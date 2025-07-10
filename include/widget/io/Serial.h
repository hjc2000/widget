#pragma once
#include "base/embedded/serial/serial_parameter.h"
#include "qserialport.h"
#include "serial_handle.h"
#include "widget/thread/Thread.h"
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

	public:
		Serial(std::string const &name)
		{
			_thread.start();

			std::shared_ptr<base::task::ITask> task = _thread.InvokeAsync(
				[this]()
				{
					{
						// 后续只能通过 std::weak_ptr<QSerialPort> _serial{} 访问，
						// 特别是 lambda 表达式不能直接按值捕获 std::shared_ptr<QSerialPort> serial,
						// 否则会出现循环引用。
						std::shared_ptr<QSerialPort> serial{new QSerialPort{}};
						_thread.AddResource(serial);
						_serial = serial;
					}
				});

			task->Wait();
		}

		~Serial()
		{
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
