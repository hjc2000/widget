#pragma once
#include <base/math/Interval.h>
#include <qlabel.h>
#include <widget/line-input-widget/Input.h>

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
	private:
		// 控件

		widget::HBoxLayout _layout{this};
		widget::Input _left_edit{};
		widget::Input _right_edit{};
		QLabel _label{"-"};

	private:
		/**
		 * @brief 提交数据时触发的事件。
		 *
		 * @note 触发条件
		 * 		@li 用户点击提交按钮。
		 * 		@li 用户在左右 2 个输入框按下回车。
		 *		@li 用户在左右 2 个输入框编辑后让输入框失去焦点。
		 */
		base::Delegate<> _submit_event;

	public:
		/**
		 * @brief Construct a new Range Submit object
		 *
		 */
		RangeSubmit();

	public:
		/**
		 * @brief 左侧输入框在没有输入内容时显示的文本。
		 *
		 * @return QString
		 */
		QString LeftPlaceholderText() const;

		/**
		 * @brief 设置左侧输入框在没有输入内容时显示的文本。
		 *
		 * @param value
		 */
		void SetLeftPlaceholderText(QString const &value);

		/**
		 * @brief 设置左侧输入框在没有输入内容时显示的文本。
		 *
		 * @param value
		 */
		void SetLeftPlaceholderText(std::string const &value);

		/**
		 * @brief 设置左侧输入框在没有输入内容时显示的文本。
		 *
		 * @param value
		 */
		void SetLeftPlaceholderText(char const *value);

		/**
		 * @brief 左侧输入框在没有输入内容时显示的文本。
		 *
		 * @return std::string
		 */
		std::string LeftPlaceholderTextStdString() const;

	public:
		/**
		 * @brief 右侧输入框在没有输入内容时显示的文本。
		 *
		 * @return QString
		 */
		QString RightPlaceholderText() const;

		/**
		 * @brief 设置右侧输入框在没有输入内容时显示的文本。
		 *
		 * @param value
		 */
		void SetRightPlaceholderText(QString const &value);

		/**
		 * @brief 设置右侧输入框在没有输入内容时显示的文本。
		 *
		 * @param value
		 */
		void SetRightPlaceholderText(std::string const &value);

		/**
		 * @brief 设置右侧输入框在没有输入内容时显示的文本。
		 *
		 * @param value
		 */
		void SetRightPlaceholderText(char const *value);

		/**
		 * @brief 右侧输入框在没有输入内容时显示的文本。
		 *
		 * @return std::string
		 */
		std::string RightPlaceholderTextStdString() const;

	public:
		/**
		 * @brief 左侧输入框的文本。
		 *
		 * @return QString
		 */
		QString LeftText() const;

		/**
		 * @brief 设置左侧输入框的文本。
		 *
		 * @param value
		 */
		void SetLeftText(QString const &value);

		/**
		 * @brief 设置左侧输入框的文本。
		 *
		 * @param value
		 */
		void SetLeftText(std::string const &value);

		/**
		 * @brief 设置左侧输入框的文本。
		 *
		 * @param value
		 */
		void SetLeftText(char const *value);

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
		 * @brief 设置左侧输入框的文本。
		 *
		 * @param value
		 */
		void SetRightText(QString const &value);

		/**
		 * @brief 设置左侧输入框的文本。
		 *
		 * @param value
		 */
		void SetRightText(std::string const &value);

		/**
		 * @brief 设置左侧输入框的文本。
		 *
		 * @param value
		 */
		void SetRightText(char const *value);

		/**
		 * @brief 右侧输入框的文本。
		 *
		 * @return std::string
		 */
		std::string RightTextStdString() const;

		/**
		 * @brief 获取区间。
		 *
		 * @return base::ClosedInterval<QString>
		 */
		base::ClosedInterval<QString> Interval() const;

	public:
		// 事件

		/**
		 * @brief 提交数据时触发的事件。
		 *
		 * @note 触发条件
		 * 		@li 用户点击提交按钮。
		 * 		@li 用户在左右 2 个输入框按下回车。
		 *		@li 用户在左右 2 个输入框编辑后让输入框失去焦点。
		 *
		 * @return base::IEvent<>&
		 */
		base::IEvent<> &SubmitEvent();

	public:
		// 输入非法

		/**
		 * @brief 设置左边输入框的输入非法样式。
		 *
		 * @param is_invalid 为 true 打开非法样式，为 false 恢复成正常样式。
		 */
		void SetLeftInvalidInputStyle(bool is_invalid);

		/**
		 * @brief 设置右边输入框的输入非法样式。
		 *
		 * @param is_invalid 为 true 打开非法样式，为 false 恢复成正常样式。
		 */
		void SetRightInvalidInputStyle(bool is_invalid);
	};
} // namespace widget
