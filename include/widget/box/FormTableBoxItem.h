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
		std::shared_ptr<QWidget> _left{};
		std::shared_ptr<QWidget> _right{};

		void Initialize();

	public:
		FormTableBoxItem() = default;

		FormTableBoxItem(std::shared_ptr<QWidget> const &left,
						 std::shared_ptr<QWidget> const &right);

		FormTableBoxItem(std::string const &left_label_text,
						 std::shared_ptr<QWidget> const &right);

	public:
		std::shared_ptr<QWidget> Left() const;
		std::shared_ptr<QWidget> Right() const;
	};
} // namespace widget
