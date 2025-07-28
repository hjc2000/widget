#pragma once
#include "base/delegate/IEvent.h"
#include "base/math/Interval.h"
#include "widget/layout/VBoxLayout.h"
#include "widget/line-input-widget/RangeSubmit.h"
#include <cstdint>

namespace widget
{
	///
	/// @brief 整型范围提交控件。
	///
	class IntRangeSubmit :
		public QWidget
	{
	private:
		widget::VBoxLayout _layout{this};
		widget::RangeSubmit _range_submit = widget::RangeSubmit{};

		int64_t _min = INT64_MIN;
		int64_t _max = INT64_MAX;

		int64_t _left_value = 0;
		int64_t _right_value = 0;

		bool TryParseLeftValue(int64_t &out);
		bool TryParseRightValue(int64_t &out);
		void CheckLeftRightValues(int64_t left_value, int64_t right_value);

		void OnSubmit();

		base::Delegate<> _submit_event;

	public:
		IntRangeSubmit();
		IntRangeSubmit(int64_t min, int64_t max);

		int64_t MinValue() const;
		void SetMinValue(int64_t value);
		int64_t MaxValue() const;
		void SetMaxValue(int64_t value);

		/* #region 区间 */

		///
		/// @brief 区间左端点。
		///
		/// @return int64_t
		///
		int64_t LeftValue() const;

		///
		/// @brief 区间右端点。
		///
		/// @return int64_t
		///
		int64_t RightValue() const;

		///
		/// @brief 获取区间。
		///
		/// @return base::ClosedInterval<int64_t>
		///
		base::ClosedInterval<int64_t> Interval() const;
		/* #endregion */

		///
		/// @brief 提交事件。
		///
		/// @return base::IEvent<>&
		///
		base::IEvent<> &SubmitEvent();

		/* #region 输入非法样式 */

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
		/* #endregion */

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
		/// @return std::string
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
		/// @brief 设置左侧输入框的文本。
		///
		/// @param value
		///
		void SetRightText(QString const &value);

		///
		/// @brief 设置左侧输入框的文本。
		///
		/// @param value
		///
		void SetRightText(std::string const &value);

		///
		/// @brief 设置左侧输入框的文本。
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
	};
} // namespace widget
