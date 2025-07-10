#pragma once
#include "base/IDisposable.h"
#include "base/task/ITask.h"
#include "qeventloop.h"
#include "qthread.h"
#include <atomic>
#include <functional>
#include <memory>

namespace widget
{
	class Thread final :
		public QThread,
		public base::IDisposable
	{
	private:
		std::function<void()> _func;
		std::atomic_bool _disposed = false;

		virtual void run() override
		{
			QEventLoop loop;
			loop.exec();
		}

	public:
		Thread()
			: QThread(nullptr)
		{
		}

		~Thread()
		{
			Dispose();
		}

		///
		/// @brief 主动释放对象，让对象不再能够工作。
		///
		///
		virtual void Dispose() override
		{
			if (_disposed)
			{
				return;
			}

			_disposed = true;

			// 发出退出信号，线程函数会在处理完当前消息队列的所有消息后退出。
			quit();

			// 等待。在 quit 事件之前的通过 InvokeAsync 方法加入消息队列的消息都能被处理，
			// 也就是 InvokeAsync 提交的任务都能被执行，InvokeAsync 方法返回的 base::task::ITask
			// 也会被设置为已完成。
			wait();

			// 断开本对象订阅的所有信号。
			QObject::disconnect(nullptr, nullptr, this, nullptr);
		}

		///
		/// @brief 将函数提交给线程排队执行。
		///
		/// @param func
		///
		/// @return 可以用来等待任务完成。
		///
		std::shared_ptr<base::task::ITask> InvokeAsync(std::function<void()> const &func);
	};

} // namespace widget
