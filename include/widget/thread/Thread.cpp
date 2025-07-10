#include "Thread.h"
#include "base/IDisposable.h"
#include "base/string/define.h"
#include "base/task/TaskCompletionSignal.h"
#include <iostream>

std::shared_ptr<base::task::ITask> widget::Thread::InvokeAsync(std::function<void()> const &func)
{
	if (_disposed)
	{
		throw base::ObjectDisposedException{};
	}

	std::shared_ptr<base::task::TaskCompletionSignal> signal{new base::task::TaskCompletionSignal{false}};

	QMetaObject::invokeMethod(this, [func, signal]()
							  {
								  base::task::TaskCompletionSignalGuard g{*signal};

								  try
								  {
									  func();
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
