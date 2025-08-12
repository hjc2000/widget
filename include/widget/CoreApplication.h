#pragma once
#include "base/ExitGuard.h"
#include "QApplication"
#include "widget/plugin.h" // IWYU pragma: keep

namespace widget
{
	class CoreApplication :
		public QApplication
	{
	private:
		base::ExitGuard _exit_guard;

	public:
		CoreApplication();

		CoreApplication(int &argc, char **argv);
	};

} // namespace widget
