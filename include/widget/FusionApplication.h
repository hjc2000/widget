#pragma once
#include "QApplication"
#include "QFont"
#include "widget/plugin.h" // IWYU pragma: keep

namespace widget
{
	class FusionApplication :
		public QApplication
	{
	private:
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
