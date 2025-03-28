#pragma once
#include "QApplication"

namespace widget
{
	class FusionApplication :
		public QApplication
	{
	private:
		void SetFont();

	public:
		FusionApplication();
		FusionApplication(int &argc, char **argv);
	};
} // namespace widget
