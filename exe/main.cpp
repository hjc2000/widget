#include "widget/CoreApplication.h"
#include "widget/FusionApplication.h"
#include "widget/MainWindow.h"
#include <iostream>

int main()
{
	{
		// widget::FusionApplication app{};
		// widget::MainWindow window{};
		// window.showMaximized();
		// return app.exec();
	}
	{
		widget::CoreApplication app{};
		std::cout << "这是一个Qt终端应用程序" << std::endl;
		return app.exec();
	}
}
