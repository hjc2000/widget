#pragma once
#include "qboxlayout.h"
#include "qwidget.h"
#include <cwchar>
#include <memory>

namespace widget
{
	class HBoxLayout
	{
	private:
		std::shared_ptr<QHBoxLayout> _layout;

	public:
		HBoxLayout(QWidget *parent);

		void AddWidget(QWidget *widget);
	};
} // namespace widget
