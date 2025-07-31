#include "serial_handle.h" // IWYU pragma: keep
#include "qserialportinfo.h"
#include "widget/convert.h"
#include "widget/io/Serial.h"

std::vector<std::string> base::serial::scan_serials()
{
	QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
	std::vector<std::string> results;

	for (auto const &port : ports)
	{
		results.push_back(base::to_string(port.portName()));
	}

	return results;
}

std::vector<base::serial::SerialPortInfomation> base::serial::scan_serials_for_details()
{
	QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
	std::vector<base::serial::SerialPortInfomation> results;

	for (auto const &port : ports)
	{
		base::serial::SerialPortInfomation info{
			base::to_string(port.portName()),
			base::to_string(port.description()),
		};

		results.push_back(info);
	}

	return results;
}

std::shared_ptr<base::serial::serial_handle> base::serial::open(std::string const &name)
{
	std::shared_ptr<base::serial::serial_handle> ret{new widget::Serial{name}};
	return ret;
}

void base::serial::start(base::serial::serial_handle &h,
						 base::serial::Direction direction,
						 base::serial::BaudRate const &baud_rate,
						 base::serial::DataBits const &data_bits,
						 base::serial::Parity parity,
						 base::serial::StopBits stop_bits,
						 base::serial::HardwareFlowControl hardware_flow_control)
{
	h.Start(direction, baud_rate, data_bits, parity, stop_bits, hardware_flow_control);
}

/* #region 串口属性 */

std::string base::serial::name(base::serial::serial_handle &h)
{
	return h.Name();
}

base::serial::Direction base::serial::direction(base::serial::serial_handle &h)
{
	return h.Direction();
}

uint32_t base::serial::baud_rate(base::serial::serial_handle &h)
{
	return h.BaudRate();
}

uint8_t base::serial::data_bits(base::serial::serial_handle &h)
{
	return h.DataBits();
}

base::serial::Parity base::serial::parity(base::serial::serial_handle &h)
{
	return h.Parity();
}

base::serial::StopBits base::serial::stop_bits(base::serial::serial_handle &h)
{
	return h.StopBits();
}

base::serial::HardwareFlowControl base::serial::hardware_flow_control(base::serial::serial_handle &h)
{
	return h.HardwareFlowControl();
}

/* #endregion */

int64_t base::serial::read(base::serial::serial_handle &h, base::Span const &span)
{
	return h.Read(span);
}

void base::serial::write(base::serial::serial_handle &h, base::ReadOnlySpan const &span)
{
	h.Write(span);
}

void base::serial::flush(base::serial::serial_handle &h)
{
	h.Flush();
}

void base::serial::close(base::serial::serial_handle &h)
{
	h.Close();
}
