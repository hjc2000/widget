#include <MainWindow.h>
#include <test_qwt.h>

int main()
{
	int argc = 1;

	char *argv[] = {
		const_cast<char *>("Hello World"),
		nullptr,
	};

	QApplication app{argc, argv};
	widget::MainWindow window{};
	window.showMaximized();
	return app.exec();
}
