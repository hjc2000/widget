#include "CoreApplication.h"

namespace
{
	int null_argc = 0;

	char *null_argv[] = {
		nullptr,
	};
} // namespace

widget::CoreApplication::CoreApplication()
	: CoreApplication(null_argc, null_argv)
{
}

widget::CoreApplication::CoreApplication(int &argc, char **argv)
	: QApplication(argc, argv)
{
}
