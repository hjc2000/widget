#include "widget/FusionApplication.h"
#include "widget/MainWindow.h"
#include <iostream>

int main()
{
	try
	{
		widget::FusionApplication app{};
		widget::MainWindow window{};
		window.showMaximized();
		return app.exec();
	}
	catch (std::exception const &e)
	{
		std::cerr << e.what() << std::endl;
		return -1;
	}
	catch (...)
	{
		std::cerr << "未知异常" << std::endl;
		return -1;
	}
}
