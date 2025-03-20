#include "FusionApplication.h"
#include "QFont"

namespace
{
	int null_argc = 0;

	char *null_argv[] = {
		nullptr,
	};
} // namespace

widget::FusionApplication::FusionApplication()
	: FusionApplication(null_argc, null_argv)
{
}

widget::FusionApplication::FusionApplication(int &argc, char **argv)
	: QApplication(argc, argv)
{
	setStyle("fusion");

	{
		// 设置全局字体

		// 获取默认字体
		QFont f = font();

		// 设置字体大小（例如12）
		f.setPointSize(16);

		// 应用到整个应用程序
		setFont(f);
	}
}
