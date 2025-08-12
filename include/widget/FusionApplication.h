#pragma once
#include "base/ExitGuard.h"
#include "QApplication"
#include "QFont"
#include "widget/plugin.h" // IWYU pragma: keep

namespace widget
{
	class FusionApplication :
		public QApplication
	{
	private:
		///
		/// @brief 使用过 std::thread 和 qt 的类交互过后，进程结束时会发生访问非法内存的异常。
		/// 调用堆栈如下：
		/// 	set_thread_data(QThreadData*)::Cleanup::~Cleanup() (@set_thread_data(QThreadData*)::Cleanup::~Cleanup():11)
		/// 	run_dtor_list (@tls_callback:34)
		/// 	run_dtor_list (@tls_callback:30)
		/// 	tls_callback (@tls_callback:26)
		/// 	RtlTimeToSecondsSince1970 (@RtlTimeToSecondsSince1970:278)
		/// 	RtlDeactivateActivationContext (@RtlDeactivateActivationContext:884)
		/// 	RtlDeactivateActivationContext (@RtlDeactivateActivationContext:644)
		/// 	LdrShutdownThread (@LdrShutdownThread:105)
		/// 	RtlExitUserThread (@RtlExitUserThread:21)
		/// 	BaseThreadInitThunk (@BaseThreadInitThunk:13)
		/// 	RtlUserThreadStart (@RtlUserThreadStart:15)
		///
		/// 即使进程函数早就退出了，std::thread 对象早就销毁了。不管等多久都没用，一定会发生上面这种异常。
		/// 因此在 APP 类的最前面组合这个字段。这样通过 RAII 机制, 这个字段会在最后被析构，调用 exit(0),
		/// 直接退出进程，不让 tls_callback 去调用 QThreadData::Cleanup::~Cleanup() 了。
		///
		/// 因为 APP 类对象应该第一个构造，所以所有类的析构函数都可以执行，应用程序的所有资源都有机会清理。
		///
		base::ExitGuard _exit_guard;

		void SetFont()
		{
			QFont qfont = font();
			qfont.setPointSize(16);
			setFont(qfont);
		}

	public:
		FusionApplication();
		FusionApplication(int &argc, char **argv);
	};

} // namespace widget
