#include "Serial.h"

void widget::Serial::OnReceiveData()
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

widget::Serial::Serial(std::string const &name)
{
	_port_name = name;

	// 委托后台线程创建串口对象并连接信号。
	{
		std::shared_ptr<base::task::ITask> task = _thread.InvokeAsync(
			[this]()
			{
				std::shared_ptr<QSerialPort> serial{new QSerialPort{}};
				_thread.AddResource(serial);
				_serial = serial.get();

				// 槽函数禁止用值捕获的方式捕获 qt 信号源对象的共享指针，因为 lambda 槽函数会被信号源
				// 对象储存，会直接导致共享指针循环引用。
				QSerialPort::connect(_serial,
									 &QSerialPort::readyRead,
									 [this]()
									 {
										 OnReceiveData();
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
		[&]()
		{
			_serial->setPortName(_port_name.c_str());
			_serial->setBaudRate(baud_rate.Value());
			_serial->setDataBits(widget::Convert<QSerialPort::DataBits>(data_bits));
			_serial->setParity(widget::Convert<QSerialPort::Parity>(parity));
			_serial->setStopBits(widget::Convert<QSerialPort::StopBits>(stop_bits));
			_serial->setFlowControl(widget::Convert<QSerialPort::FlowControl>(hardware_flow_control));

			_serial->open(widget::Convert<QIODeviceBase::OpenModeFlag>(direction));
		});

	task->Wait();
}
