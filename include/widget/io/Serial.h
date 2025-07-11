#pragma once
#include "base/embedded/serial/serial_parameter.h"
#include "base/stream/BlockingCircleBufferMemoryStream.h"
#include "base/stream/ReadOnlySpan.h"
#include "qserialport.h"
#include "serial_handle.h"
#include "widget/thread/Thread.h"
#include <cstdint>
#include <memory>
#include <string>

namespace widget
{
	class Serial :
		public base::serial::serial_handle
	{
	private:
		widget::Thread _thread{};
		std::string _port_name{};
		base::BlockingCircleBufferMemoryStream _received_stream{1024 * 10};

		///
		/// @brief 后台线程中创建对象后赋值给本弱指针。后台线程退出前要负责析构，
		/// 所以这里不能直接持有共享指针，否则会阻止后台线程对串口对象的析构。
		///
		QSerialPort *_serial{};

		void OnReceiveData()
		{
			if (_received_stream.AvailableToWrite() == 0)
			{
				return;
			}

			QByteArray receive_data = _serial->readAll();

			base::ReadOnlySpan span{
				reinterpret_cast<uint8_t const *>(receive_data.data()),
				static_cast<int32_t>(receive_data.size()),
			};

			_received_stream.Write(span);
		}

	public:
		Serial(std::string const &name);

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
			std::shared_ptr<base::task::ITask> task = _thread.InvokeAsync(
				[this]()
				{
					_serial->setPortName(_port_name.c_str());

					_serial->setBaudRate(115200);

					// 设置数据位
					_serial->setDataBits(QSerialPort::DataBits::Data8);

					// 设置校验位
					_serial->setParity(QSerialPort::Parity::NoParity);

					// 设置停止位
					_serial->setStopBits(QSerialPort::StopBits::OneStop);

					// 设置流控制
					_serial->setFlowControl(QSerialPort::FlowControl::NoFlowControl);

					_serial->open(QIODeviceBase::OpenModeFlag::ReadWrite);
				});

			task->Wait();
		}

		virtual int32_t Read(base::Span const &span) override
		{
			return _received_stream.Read(span);
		}

		virtual void Write(base::ReadOnlySpan const &span) override
		{
		}

		virtual void Flush() override
		{
		}
	};

} // namespace widget
