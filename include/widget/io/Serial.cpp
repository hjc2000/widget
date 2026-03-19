#include "Serial.h"
#include <iostream>

void widget::Serial::OnReceiveData(QSerialPort &serial)
{
	try
	{
		if (_received_stream.AvailableToWrite() == 0)
		{
			return;
		}

		QByteArray receive_data = serial.readAll();

		base::ReadOnlySpan span{
			reinterpret_cast<uint8_t const *>(receive_data.data()),
			static_cast<int64_t>(receive_data.size()),
		};

		_received_stream.Write(span);
	}
	catch (std::exception const &e)
	{
		std::cerr << CODE_POS_STR + e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << CODE_POS_STR + "未知异常。" << std::endl;
	}
}

widget::Serial::Serial(std::string const &name)
{
	_port_name = name;

	// 委托后台线程创建串口对象并连接信号。
	{
		std::shared_ptr<base::task::ITask> task = _thread.InvokeAsync(
			[this](widget::ThreadResourceManager &thread_resource_manager)
			{
				{
					std::shared_ptr<QSerialPort> serial{new QSerialPort{}};
					thread_resource_manager.Add(ThreadResourceIdProvider::SerialPort(), serial);
				}

				QSerialPort &serial = thread_resource_manager.Get<QSerialPort>(ThreadResourceIdProvider::SerialPort());

				// 槽函数禁止用值捕获的方式捕获 qt 信号源对象的共享指针，因为 lambda 槽函数会被信号源
				// 对象储存，会直接导致共享指针循环引用。
				QSerialPort::connect(&serial,
									 &QSerialPort::readyRead,
									 [this, &serial]()
									 {
										 OnReceiveData(serial);
									 });
			});

		task->Wait();
	}
}

void widget::Serial::Start(base::serial::Direction direction,
						   base::serial::BaudRate const &baud_rate,
						   base::serial::DataBits const &data_bits,
						   base::serial::Parity parity,
						   base::serial::StopBits stop_bits,
						   base::serial::HardwareFlowControl hardware_flow_control)
{
	_direction = direction;
	_baud_rate = baud_rate;
	_data_bits = data_bits;
	_parity = parity;
	_stop_bits = stop_bits;
	_hardware_flow_control = hardware_flow_control;

	std::shared_ptr<base::task::ITask> task = _thread.InvokeAsync(
		[&](widget::ThreadResourceManager &thread_resource_manager)
		{
			QSerialPort &serial = thread_resource_manager.Get<QSerialPort>(ThreadResourceIdProvider::SerialPort());

			serial.setPortName(_port_name.c_str());
			serial.setBaudRate(baud_rate.Value());
			serial.setDataBits(widget::Convert<QSerialPort::DataBits>(data_bits));
			serial.setParity(widget::Convert<QSerialPort::Parity>(parity));
			serial.setStopBits(widget::Convert<QSerialPort::StopBits>(stop_bits));
			serial.setFlowControl(widget::Convert<QSerialPort::FlowControl>(hardware_flow_control));

			serial.open(widget::Convert<QIODeviceBase::OpenModeFlag>(direction));
		});

	task->Wait();
}
