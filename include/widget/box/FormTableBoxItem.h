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
	class FormTableBoxItem
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
		FormTableBoxItem(std::string const &label, std::shared_ptr<QWidget> const &widget);

	public:
		/**
		 * @brief 标签。
		 *
		 * @return std::string
		 */
		std::string Label() const;

		/**
		 * @brief 控件。
		 *
		 * @return std::shared_ptr<QWidget>
		 */
		std::shared_ptr<QWidget> Widget() const;
	};
} // namespace widget
