#pragma once
#include "base/embedded/serial/serial_parameter.h"
#include "qserialport.h"
#include "serial_handle.h"
#include <memory>
#include <string>

namespace widget
{
	class Serial :
		public base::serial::serial_handle
	{
	private:
		class Thread;

		std::weak_ptr<QSerialPort> _serial{};
		std::shared_ptr<Thread> _thread{};

	public:
		Serial(std::string const &name)
		{
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
