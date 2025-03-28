#include "widget/FusionApplication.h"
#include "widget/MainWindow.h"

int main()
{
	widget::FusionApplication app{};
	widget::MainWindow window{};
	window.showMaximized();
	return app.exec();
}
