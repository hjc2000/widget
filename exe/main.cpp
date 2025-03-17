#include "widget/FusionApplication.h"
#include "widget/MainWindow.h"
#include <widget/test_qwt.h>
#include <widget/test_qxlsx.h>

// int main()
// {
// 	try
// 	{
// 		int argc = 1;

// 		char *argv[] = {
// 			const_cast<char *>("Hello World"),
// 			nullptr,
// 		};

// 		widget::FusionApplication app{argc, argv};
// 		widget::MainWindow window{};
// 		window.showMaximized();
// 		return app.exec();
// 	}
// 	catch (std::exception const &e)
// 	{
// 		std::cerr << e.what() << std::endl;
// 		return -1;
// 	}
// 	catch (...)
// 	{
// 		std::cerr << "未知异常" << std::endl;
// 		return -1;
// 	}
// }

int main()
{
	// widget::test_qwt();
	widget::test_qxlsx();
}
