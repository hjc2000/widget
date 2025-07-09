#include "widget/CoreApplication.h"
#include "widget/FusionApplication.h"
#include "widget/MainWindow.h"
#include <iostream>

int TestFusionApplication()
{
	widget::FusionApplication app{};
	widget::MainWindow window{};
	window.showMaximized();
	return app.exec();
}

int TestCoreApplication()
{
	widget::CoreApplication app{};
	std::cout << "这是一个Qt终端应用程序" << std::endl;
	return app.exec();
}

int main()
{
	return TestCoreApplication();
}
