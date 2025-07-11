#include "Serial.h"

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
