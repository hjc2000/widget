#pragma once
#include "base/embedded/serial/serial_handle.h"
#include <cstdint>

class base::serial::serial_handle
{
public:
	virtual void Start(base::serial::Direction direction,
					   base::serial::BaudRate const &baud_rate,
					   base::serial::DataBits const &data_bits,
					   base::serial::Parity parity,
					   base::serial::StopBits stop_bits,
					   base::serial::HardwareFlowControl hardware_flow_control) = 0;

	virtual int32_t Read(base::Span const &span) = 0;

	virtual void Write(base::ReadOnlySpan const &span) = 0;

	virtual void Flush() = 0;
};
