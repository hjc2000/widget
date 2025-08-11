#pragma once
#include "qwidget.h"

namespace widget
{
	class IndependentQWidget :
		public QWidget
	{
	public:
		IndependentQWidget()
			: QWidget(nullptr)
		{
		}

		virtual ~IndependentQWidget()
		{
			setParent(nullptr);
		}
	};

} // namespace widget
