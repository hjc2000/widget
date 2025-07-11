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

///
/// @brief 获取串口名称。
///
/// @param h
/// @return std::string
///
std::string base::serial::name(base::serial::serial_handle &h)
{
	return h.Name();
}

///
/// @brief 数据传输方向。
///
/// @param h
/// @return base::serial::Direction
///
base::serial::Direction base::serial::direction(base::serial::serial_handle &h)
{
	return h.Direction();
}

///
/// @brief 波特率。
///
/// @param h
/// @return uint32_t
///
uint32_t base::serial::baud_rate(base::serial::serial_handle &h)
{
	return h.BaudRate();
}

///
/// @brief 数据位的个数。
///
/// @param h
/// @return uint8_t
///
uint8_t base::serial::data_bits(base::serial::serial_handle &h)
{
	return h.DataBits();
}

///
/// @brief 校验位。
///
/// @param h
/// @return base::serial::Parity
///
base::serial::Parity base::serial::parity(base::serial::serial_handle &h)
{
	return h.Parity();
}

///
/// @brief 停止位个数。
///
/// @param h
/// @return base::serial::StopBits
///
base::serial::StopBits base::serial::stop_bits(base::serial::serial_handle &h)
{
	return h.StopBits();
}

///
/// @brief 硬件流控。
///
/// @param h
/// @return base::serial::HardwareFlowControl
///
base::serial::HardwareFlowControl base::serial::hardware_flow_control(base::serial::serial_handle &h)
{
	return h.HardwareFlowControl();
}

/* #endregion */

int32_t base::serial::read(base::serial::serial_handle &h, base::Span const &span)
{
	return h.Read(span);
}

///
/// @brief 向串口写入数据。
///
/// @param h
/// @param span
///
void base::serial::write(base::serial::serial_handle &h, base::ReadOnlySpan const &span)
{
	h.Write(span);
}

///
/// @brief 冲洗串口。
///
/// @param h
///
void base::serial::flush(base::serial::serial_handle &h)
{
	h.Flush();
}
