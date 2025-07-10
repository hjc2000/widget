#pragma once
#include "base/Console.h"
#include "base/string/define.h"
#include "qeventloop.h"
#include "qthread.h"
#include <functional>

namespace widget
{
	class Thread final :
		QThread
	{
	private:
		std::function<void()> _func;

		virtual void run() override
		{
			QEventLoop loop;
			if (_func)
			{
				try
				{
					_func();
				}
				catch (std::exception const &e)
				{
					base::console.WriteError(CODE_POS_STR + e.what());
					return;
				}
				catch (...)
				{
					base::console.WriteError(CODE_POS_STR + "未知异常。");
					return;
				}
			}

			loop.exec();
		}

	public:
		Thread()
			: QThread(nullptr)
		{
		}

		///
		/// @brief
		///
		/// @param func 线程启动时会被执行的函数。
		///
		Thread(std::function<void()> func)
			: QThread(nullptr)
		{
			_func = func;
		}
	};

} // namespace widget
