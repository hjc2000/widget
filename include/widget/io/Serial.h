#pragma once
#include "base/embedded/serial/serial_parameter.h"
#include "qserialport.h"
#include "serial_handle.h"
#include "widget/thread/Thread.h"
#include <iostream>
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

		///
		/// @brief 后台线程中创建对象后赋值给本弱指针。后台线程退出前要负责析构，
		/// 所以这里不能直接持有共享指针，否则会阻止后台线程对串口对象的析构。
		///
		QSerialPort *_serial{};

		void OnReceiveData()
		{
			QByteArray receive_data = _serial->readAll();
			std::cout.write(receive_data.data(), receive_data.size());
		}

	public:
		Serial(std::string const &name)
		{
			_port_name = name;

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
