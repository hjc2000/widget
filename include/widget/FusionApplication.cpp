#include "FusionApplication.h" // IWYU pragma: keep

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
	SetFont();
}
