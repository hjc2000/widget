#pragma once
#include <base/delegate/IEvent.h>
#include <cstdint>
#include <widget/line-input-widget/RangeSubmit.h>

namespace widget
{
	/**
	 * @brief 整型范围提交控件。
	 *
	 */
	class IntRangeSubmit :
		public QWidget
	{
	private:
		widget::HBoxLayout _layout{this};
		widget::RangeSubmit _range_submit = widget::RangeSubmit{};

	private:
		int64_t _min = INT64_MIN;
		int64_t _max = INT64_MAX;

		int64_t _left_value = 0;
		int64_t _right_value = 0;
		int64_t ParseLeftValue() const;
		int64_t ParseRightValue() const;
		void OnSubmit();

	private:
		base::Delegate<> _submit_event;

	public:
		IntRangeSubmit();

		IntRangeSubmit(int64_t min, int64_t max);

	public:
		int64_t MinValue() const;
		void SetMinValue(int64_t value);
		int64_t MaxValue() const;
		void SetMaxValue(int64_t value);

	public:
		int64_t LeftValue() const;
		int64_t RightValue() const;

	public:
		base::IEvent<> &SubmitEvent();

	public:
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

	public:
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
	};
} // namespace widget
