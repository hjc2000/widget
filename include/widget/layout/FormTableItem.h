#pragma once
#include "qwidget.h"
#include <memory>
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
		std::shared_ptr<QWidget> _widget{};

	public:
		/**
		 * @brief Construct a new Form Table Item object
		 *
		 * @param label
		 * @param widget
		 */
		FormTableItem(std::string const &label, std::shared_ptr<QWidget> const &widget);

	public:
		std::string Label() const;

		std::shared_ptr<QWidget> Widget() const;
	};
} // namespace widget
