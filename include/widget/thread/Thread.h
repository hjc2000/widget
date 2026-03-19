#pragma once
#include "base/IDisposable.h"
#include "base/string/define.h"
#include "base/task/ITask.h"
#include "base/task/TaskCompletionSignal.h"
#include "qeventloop.h"
#include "qobject.h"
#include "qthread.h"
#include "ThreadResourceManager.h"
#include <atomic>
#include <functional>
#include <iostream>
#include <memory>

namespace widget
{
	class Thread final :
		private QThread,
		public base::IDisposable
	{
	private:
		std::function<void()> _func;
		std::atomic_bool _disposed = false;
		widget::ThreadResourceManager _resource_manager{};

		///
		/// @brief 线程启动后构造一个 QObject 对象，将指针赋值到本字段。
		///
		QObject *_object{};

		///
		/// @brief 线程启动后就设置本信号的结果。
		///
		base::task::TaskCompletionSignal _thread_started{false};

		///
		/// @brief 重写 QThread 的 run.
		/// 这个函数是线程启动后的线程函数。
		///
		virtual void run() override
		{
			QEventLoop loop;
			QObject object;
			_object = &object;
			_thread_started.SetResult();
			loop.exec();
			_resource_manager.Clear();
			_object = nullptr;
		}

	public:
		Thread()
			: QThread(nullptr)
		{
			start();
			_thread_started.Wait();
		}

		~Thread()
		{
			Dispose();
		}

		///
		/// @brief 处置对象，让对象准备好结束生命周期。类似于进入 “准备后事” 的状态。
		///
		/// @note 注意，对象并不是析构了，并不是完全无法访问，它仍然允许访问，仍然能执行一些
		/// 符合 “准备后事” 的工作。
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
		}

		///
		/// @brief 将函数提交给线程排队执行。
		///
		/// @param func
		///
		/// @return 可以用来等待任务完成。
		///
		std::shared_ptr<base::task::ITask> InvokeAsync(std::function<void(widget::ThreadResourceManager &thread_resource_manager)> const &func)
		{
			if (_disposed)
			{
				throw base::ObjectDisposedException{};
			}

			std::shared_ptr<base::task::TaskCompletionSignal> signal{new base::task::TaskCompletionSignal{false}};

			QMetaObject::invokeMethod(
				_object,
				[func, signal, this]()
				{
					base::task::TaskCompletionSignalGuard g{*signal};

					try
					{
						func(_resource_manager);
					}
					catch (std::exception const &e)
					{
						std::cerr << CODE_POS_STR << e.what() << std::endl;
					}
					catch (...)
					{
						std::cerr << CODE_POS_STR << "未知的异常。" << std::endl;
					}
				},
				Qt::QueuedConnection);

			return signal;
		}
	};

} // namespace widget
