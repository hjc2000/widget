#pragma once
#include "base/ExitGuard.h"
#include "QApplication"
#include "QFont"
#include "widget/plugin.h" // IWYU pragma: keep

namespace widget
{
	class FusionApplication :
		public QApplication
	{
	private:
		base::ExitGuard _exit_guard;

		void SetFont()
		{
			QFont qfont = font();
			qfont.setPointSize(16);
			setFont(qfont);
		}

	public:
		FusionApplication();
		FusionApplication(int &argc, char **argv);
	};

} // namespace widget
