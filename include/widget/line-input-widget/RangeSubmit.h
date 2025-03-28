#pragma once
#include "qlabel.h"
#include "widget/line-input-widget/Input.h"

namespace widget
{
	///
	/// @brief 提交一个范围。
	///
	/// @note 分成左右 2 个输入框，2 个输入框中间一条短横线，表示 从...到... ，右侧一个提交按钮，
	/// 点击后就是确认提交。
	///
	class RangeSubmit :
		public QWidget
	{
	private:
		widget::HBoxLayout _layout{this};
		widget::Input _left_edit{};
		widget::Input _right_edit{};
		QLabel _label{"-"};

		///
		/// @brief 提交数据时触发的事件。
		///
		/// @note 触发条件
		/// 	@li 用户点击提交按钮。
		/// 	@li 用户在左右 2 个输入框按下回车。
		/// 	@li 用户在左右 2 个输入框编辑后让输入框失去焦点。
		///
		base::Delegate<> _submit_event;

	public:
		RangeSubmit();

		/* #region PlaceholderText */

		///
		/// @brief 左侧输入框在没有输入内容时显示的文本。
		///
		/// @return QString
		///
		QString LeftPlaceholderText() const;

		///
		/// @brief 设置左侧输入框在没有输入内容时显示的文本。
		///
		/// @param value
		///
		void SetLeftPlaceholderText(QString const &value);

		///
		/// @brief 设置左侧输入框在没有输入内容时显示的文本。
		///
		/// @param value
		///
		void SetLeftPlaceholderText(std::string const &value);

		///
		/// @brief 设置左侧输入框在没有输入内容时显示的文本。
		///
		/// @param value
		///
		void SetLeftPlaceholderText(char const *value);

		///
		/// @brief 左侧输入框在没有输入内容时显示的文本。
		///
		/// @return std::string
		///
		std::string LeftPlaceholderTextStdString() const;

		///
		/// @brief 右侧输入框在没有输入内容时显示的文本。
		///
		/// @return QString
		///
		QString RightPlaceholderText() const;

		///
		/// @brief 设置右侧输入框在没有输入内容时显示的文本。
		///
		/// @param value
		///
		void SetRightPlaceholderText(QString const &value);

		///
		/// @brief 设置右侧输入框在没有输入内容时显示的文本。
		///
		/// @param value
		///
		void SetRightPlaceholderText(std::string const &value);

		///
		/// @brief 设置右侧输入框在没有输入内容时显示的文本。
		///
		/// @param value
		///
		void SetRightPlaceholderText(char const *value);

		///
		/// @brief 右侧输入框在没有输入内容时显示的文本。
		///
		/// @param value
		///
		std::string RightPlaceholderTextStdString() const;

		/* #endregion */

		/* #region 输入框的文本 */

		///
		/// @brief 左侧输入框的文本。
		///
		/// @return QString
		///
		QString LeftText() const;

		///
		/// @brief 设置左侧输入框的文本。
		///
		/// @param value
		///
		void SetLeftText(QString const &value);

		///
		/// @brief 设置左侧输入框的文本。
		///
		/// @param value
		///
		void SetLeftText(std::string const &value);

		///
		/// @brief 设置左侧输入框的文本。
		///
		/// @param value
		///
		void SetLeftText(char const *value);

		///
		/// @brief 左侧输入框的文本。
		///
		/// @return std::string
		///
		std::string LeftTextStdString() const;

		///
		/// @brief 右侧输入框的文本。
		///
		/// @return QString
		///
		QString RightText() const;

		///
		/// @brief 设置右侧输入框的文本。
		///
		/// @param value
		///
		void SetRightText(QString const &value);

		///
		/// @brief 设置右侧输入框的文本。
		///
		/// @param value
		///
		void SetRightText(std::string const &value);

		///
		/// @brief 设置右侧输入框的文本。
		///
		/// @param value
		///
		void SetRightText(char const *value);

		///
		/// @brief 右侧输入框的文本。
		///
		/// @return std::string
		///
		std::string RightTextStdString() const;

		/* #endregion */

		///
		/// @brief 提交数据时触发的事件。
		///
		/// @note 触发条件
		/// 	@li 用户在左右 2 个输入框中的任意一个按下回车。
		/// 	@li 用户在左右 2 个输入框中的任意一个编辑后让输入框失去焦点。
		///
		/// @return base::IEvent<>&
		///
		base::IEvent<> &SubmitEvent();

		///
		/// @brief 设置左边输入框的输入非法样式。
		///
		/// @param is_invalid 为 true 打开非法样式，为 false 恢复成正常样式。
		///
		void SetLeftInvalidInputStyle(bool is_invalid);

		///
		/// @brief 设置右边输入框的输入非法样式。
		///
		/// @param is_invalid 为 true 打开非法样式，为 false 恢复成正常样式。
		///
		void SetRightInvalidInputStyle(bool is_invalid);
	};
} // namespace widget
