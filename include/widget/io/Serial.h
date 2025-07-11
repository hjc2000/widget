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
		QSerialPort *_serial{};

		void OnReceiveData();

	public:
		Serial(std::string const &name);

		~Serial()
		{
			_thread.Dispose();
			_serial = nullptr;
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
	};

} // namespace widget
