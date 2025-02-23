#pragma once
#include "qwidget.h"
#include <string>

namespace widget
{
	/**
	 * @brief 表单的项目。
	 *
	 */
	class FormTableItem
	{
	private:
		std::string _label{};
		QWidget *_widget{};

	public:
		FormTableItem() = default;

		FormTableItem(std::string const &label, QWidget *widget);

	public:
		std::string Label() const;

		QWidget *Widget() const;
	};
} // namespace widget
