#include "FusionApplication.h"
#include "QFont"

namespace
{
	int null_argc = 0;

	char *null_argv[] = {
		nullptr,
	};
} // namespace

void widget::FusionApplication::SetFont()
{
	QFont qfont = font();
	qfont.setPointSize(16);
	setFont(qfont);
}

widget::FusionApplication::FusionApplication()
	: FusionApplication(null_argc, null_argv)
{
}

widget::FusionApplication::FusionApplication(int &argc, char **argv)
	: QApplication(argc, argv)
{
	setStyle("fusion");
	SetFont();
}
