#pragma once
#include "Input.h"
#include "qboxlayout.h"
#include "qlabel.h"
#include "qvalidator.h"
#include "widget/Button.h"

namespace widget
{
	/**
	 * @brief 提交一个范围。
	 *
	 * @note 分成左右 2 个输入框，2 个输入框中间一条短横线，表示 从...到... ，右侧一个提交按钮，
	 * 点击后就是确认提交。
	 */
	class RangeSubmit :
		public QWidget
	{
	private: // 控件
		QHBoxLayout _layout{this};
		widget::Input _left_edit{};
		widget::Input _right_edit{};
		QLabel _label{"-"};
		widget::Button _button{};

	private:
		QIntValidator _validator{0, INT_MAX};
		base::Delegate<> _submit_event;

	public:
		RangeSubmit();

	public: // 属性
		/**
		 * @brief 左侧输入框的文本。
		 *
		 * @return QString
		 */
		QString LeftText() const;

		/**
		 * @brief 左侧输入框的文本。
		 *
		 * @return std::string
		 */
		std::string LeftTextStdString() const;

		/**
		 * @brief 右侧输入框的文本。
		 *
		 * @return QString
		 */
		QString RightText() const;

		/**
		 * @brief 右侧输入框的文本。
		 *
		 * @return std::string
		 */
		std::string RightTextStdString() const;

	public: // 事件
		/**
		 * @brief 用户点击提交按钮后触发的事件。
		 *
		 * @return base::IEvent<>&
		 */
		base::IEvent<> &SubmitEvent();
	};
} // namespace widget
