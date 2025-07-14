#pragma once
#include "base/embedded/serial/serial_parameter.h"
#include "base/stream/BlockingCircleBufferMemoryStream.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/string/define.h"
#include "qserialport.h"
#include "serial_handle.h"
#include "widget/thread/Thread.h"
#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>

namespace widget
{
	/* #region Convert */

	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, QIODeviceBase::OpenModeFlag>)
	constexpr ReturnType Convert(base::serial::Direction value)
	{
		switch (value)
		{
		case base::serial::Direction::RX:
			{
				return QIODeviceBase::OpenModeFlag::ReadOnly;
			}
		case base::serial::Direction::TX:
			{
				return QIODeviceBase::OpenModeFlag::WriteOnly;
			}
		case base::serial::Direction::RX_TX:
			{
				return QIODeviceBase::OpenModeFlag::ReadWrite;
			}
		default:
			{
				throw std::invalid_argument{CODE_POS_STR + "不支持的方向。"};
			}
		}
	}

	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, base::serial::Direction>)
	constexpr ReturnType Convert(QIODeviceBase::OpenModeFlag value)
	{
		switch (value)
		{
		case QIODeviceBase::OpenModeFlag::ReadOnly:
			{
				return base::serial::Direction::RX;
			}
		case QIODeviceBase::OpenModeFlag::WriteOnly:
			{
				return base::serial::Direction::TX;
			}
		case QIODeviceBase::OpenModeFlag::ReadWrite:
			{
				return base::serial::Direction::RX_TX;
			}
		default:
			{
				throw std::invalid_argument{CODE_POS_STR + "不支持的方向。"};
			}
		}
	}

	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, QSerialPort::DataBits>)
	constexpr ReturnType Convert(base::serial::DataBits const &value)
	{
		switch (value.Value())
		{
		case 5:
			{
				return QSerialPort::DataBits::Data5;
			}
		case 6:
			{
				return QSerialPort::DataBits::Data6;
			}
		case 7:
			{
				return QSerialPort::DataBits::Data7;
			}
		case 8:
			{
				return QSerialPort::DataBits::Data8;
			}
		default:
			{
				throw std::invalid_argument{CODE_POS_STR + "不支持的数据位数。"};
			}
		}
	}

	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, base::serial::DataBits>)
	constexpr ReturnType Convert(QSerialPort::DataBits value)
	{
		switch (value)
		{
		case QSerialPort::DataBits::Data5:
			{
				return base::serial::DataBits{5};
			}
		case QSerialPort::DataBits::Data6:
			{
				return base::serial::DataBits{6};
			}
		case QSerialPort::DataBits::Data7:
			{
				return base::serial::DataBits{7};
			}
		case QSerialPort::DataBits::Data8:
			{
				return base::serial::DataBits{8};
			}
		default:
			{
				throw std::invalid_argument{CODE_POS_STR + "不支持的数据位数。"};
			}
		}
	}

	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, base::serial::Parity>)
	constexpr ReturnType Convert(QSerialPort::Parity value)
	{
		switch (value)
		{
		case QSerialPort::Parity::OddParity:
			{
				return base::serial::Parity::Odd;
			}
		case QSerialPort::Parity::EvenParity:
			{
				return base::serial::Parity::Even;
			}
		case QSerialPort::Parity::NoParity:
			{
				return base::serial::Parity::None;
			}
		default:
			{
				throw std::invalid_argument{CODE_POS_STR + "不支持的校验方式。"};
			}
		}
	}

	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, QSerialPort::Parity>)
	constexpr ReturnType Convert(base::serial::Parity value)
	{
		switch (value)
		{
		case base::serial::Parity::Odd:
			{
				return QSerialPort::Parity::OddParity;
			}
		case base::serial::Parity::Even:
			{
				return QSerialPort::Parity::EvenParity;
			}
		case base::serial::Parity::None:
			{
				return QSerialPort::Parity::NoParity;
			}
		default:
			{
				throw std::invalid_argument{CODE_POS_STR + "不支持的校验方式。"};
			}
		}
	}

	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, QSerialPort::StopBits>)
	constexpr ReturnType Convert(base::serial::StopBits value)
	{
		switch (value)
		{
		case base::serial::StopBits::One:
			{
				return QSerialPort::StopBits::OneStop;
			}
		case base::serial::StopBits::OnePointFive:
			{
				return QSerialPort::StopBits::OneAndHalfStop;
			}
		case base::serial::StopBits::Two:
			{
				return QSerialPort::StopBits::TwoStop;
			}
		default:
			{
				throw std::invalid_argument{CODE_POS_STR + "不支持的停止位个数。"};
			}
		}
	}

	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, base::serial::StopBits>)
	constexpr ReturnType Convert(QSerialPort::StopBits value)
	{
		switch (value)
		{
		case QSerialPort::StopBits::OneStop:
			{
				return base::serial::StopBits::One;
			}
		case QSerialPort::StopBits::OneAndHalfStop:
			{
				return base::serial::StopBits::OnePointFive;
			}
		case QSerialPort::StopBits::TwoStop:
			{
				return base::serial::StopBits::Two;
			}
		default:
			{
				throw std::invalid_argument{CODE_POS_STR + "不支持的停止位个数。"};
			}
		}
	}

	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, QSerialPort::FlowControl>)
	constexpr ReturnType Convert(base::serial::HardwareFlowControl value)
	{
		switch (value)
		{
		case base::serial::HardwareFlowControl::None:
			{
				return QSerialPort::FlowControl::NoFlowControl;
			}
		case base::serial::HardwareFlowControl::RTS_CTS:
			{
				return QSerialPort::FlowControl::HardwareControl;
			}
		default:
			{
				throw std::invalid_argument{CODE_POS_STR + "不支持的流控方式。"};
			}
		}
	}

	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, base::serial::HardwareFlowControl>)
	constexpr ReturnType Convert(QSerialPort::FlowControl value)
	{
		switch (value)
		{
		case QSerialPort::FlowControl::NoFlowControl:
			{
				return base::serial::HardwareFlowControl::None;
			}
		case QSerialPort::FlowControl::HardwareControl:
			{
				return base::serial::HardwareFlowControl::RTS_CTS;
			}
		default:
			{
				throw std::invalid_argument{CODE_POS_STR + "不支持的流控方式。"};
			}
		}
	}

	/* #endregion */

	class Serial :
		public base::serial::serial_handle
	{
	private:
		widget::Thread _thread{};
		std::string _port_name{};
		base::BlockingCircleBufferMemoryStream _received_stream{1024 * 10};
		QSerialPort *_serial{};
		bool _closed = false;

		base::serial::Direction _direction{};
		base::serial::BaudRate _baud_rate{115200};
		base::serial::DataBits _data_bits{8};
		base::serial::Parity _parity{};
		base::serial::StopBits _stop_bits{};
		base::serial::HardwareFlowControl _hardware_flow_control{};

		void OnReceiveData();

	public:
		Serial(std::string const &name);

		~Serial()
		{
			Close();
		}

		virtual void Start(base::serial::Direction direction,
						   base::serial::BaudRate const &baud_rate,
						   base::serial::DataBits const &data_bits,
						   base::serial::Parity parity,
						   base::serial::StopBits stop_bits,
						   base::serial::HardwareFlowControl hardware_flow_control) override;

		virtual int32_t Read(base::Span const &span) override
		{
			return _received_stream.Read(span);
		}

		virtual void Write(base::ReadOnlySpan const &span) override
		{
			std::shared_ptr<base::task::ITask> task = _thread.InvokeAsync(
				[&]()
				{
					_serial->write(reinterpret_cast<char const *>(span.Buffer()),
								   span.Size());
				});

			// 写入必须等待，因为引用捕获的 span 只在本函数没有返回时有效。
			task->Wait();
		}

		virtual void Flush() override
		{
			std::shared_ptr<base::task::ITask> task = _thread.InvokeAsync(
				[&]()
				{
					_serial->flush();
				});

			task->Wait();
		}

		virtual void Close() override
		{
			if (_closed)
			{
				return;
			}

			_closed = true;

			_received_stream.Close();
			_thread.Dispose();
			_serial = nullptr;
		}

		/* #region 串口信息 */

		virtual std::string Name() const override
		{
			return _port_name;
		}

		virtual base::serial::Direction Direction() const override
		{
			return _direction;
		}

		virtual uint32_t BaudRate() const override
		{
			return _baud_rate.Value();
		}

		virtual uint8_t DataBits() const override
		{
			return _data_bits.Value();
		}

		virtual base::serial::Parity Parity() const override
		{
			return _parity;
		}

		virtual base::serial::StopBits StopBits() const override
		{
			return _stop_bits;
		}

		virtual base::serial::HardwareFlowControl HardwareFlowControl() const override
		{
			return _hardware_flow_control;
		}

		/* #endregion */
	};

} // namespace widget
