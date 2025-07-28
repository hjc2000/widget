#pragma once
#include "base/delegate/IEvent.h"
#include "base/math/Interval.h"
#include "base/string/define.h"
#include "base/string/Parse.h"
#include "widget/layout/VBoxLayout.h"
#include "widget/line-input-widget/RangeSubmit.h"
#include <cstdint>
#include <iostream>

namespace widget
{
	///
	/// @brief 整型范围提交控件。
	///
	class IntRangeSubmit final :
		public QWidget
	{
	private:
		widget::VBoxLayout _layout{this};
		widget::RangeSubmit _range_submit = widget::RangeSubmit{};

		int64_t _min = INT64_MIN;
		int64_t _max = INT64_MAX;

		int64_t _left_value = 0;
		int64_t _right_value = 0;

		bool TryParseLeftValue(int64_t &out)
		{
			try
			{
				out = base::ParseInt64(_range_submit.LeftTextStdString());
				return true;
			}
			catch (std::exception const &e)
			{
				SetLeftInvalidInputStyle(true);
				std::cerr << CODE_POS_STR + e.what() << std::endl;
			}
			catch (...)
			{
				SetLeftInvalidInputStyle(true);
				std::cerr << CODE_POS_STR + "发生了未知错误" << std::endl;
			}

			return false;
		}

		bool TryParseRightValue(int64_t &out)
		{
			try
			{
				out = base::ParseInt64(_range_submit.RightTextStdString());
				return true;
			}
			catch (std::exception const &e)
			{
				SetRightInvalidInputStyle(true);
				std::cerr << CODE_POS_STR + e.what() << std::endl;
			}
			catch (...)
			{
				SetRightInvalidInputStyle(true);
				std::cerr << CODE_POS_STR + "发生了未知错误" << std::endl;
			}

			return false;
		}

		void CheckLeftRightValues(int64_t left_value, int64_t right_value);

		void OnSubmit();

		base::Delegate<> _submit_event;

	public:
		IntRangeSubmit()
		{
			setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
			_layout.AddWidget(&_range_submit);

			_range_submit.SubmitEvent().Subscribe([this]()
												  {
													  OnSubmit();
												  });

			_range_submit.SetLeftText(std::to_string(_left_value));
			_range_submit.SetRightText(std::to_string(_right_value));
		}

		IntRangeSubmit(int64_t min, int64_t max)
			: IntRangeSubmit()
		{
			if (min > max)
			{
				throw std::invalid_argument{CODE_POS_STR + "最小值不能大于最大值。"};
			}

			_min = min;
			_max = max;
		}

		int64_t MinValue() const
		{
			return _min;
		}

		void SetMinValue(int64_t value)
		{
			_min = value;
		}

		int64_t MaxValue() const
		{
			return _max;
		}

		void SetMaxValue(int64_t value)
		{
			_max = value;
		}

		/* #region 区间 */

		///
		/// @brief 区间左端点。
		///
		/// @return
		///
		int64_t LeftValue() const
		{
			return _left_value;
		}

		///
		/// @brief 区间右端点。
		///
		/// @return
		///
		int64_t RightValue() const
		{
			return _right_value;
		}

		///
		/// @brief 获取区间。
		///
		/// @return
		///
		base::ClosedInterval<int64_t> Interval() const
		{
			return base::ClosedInterval<int64_t>{LeftValue(), RightValue()};
		}

		/* #endregion */

		///
		/// @brief 提交事件。
		///
		/// @return
		///
		base::IEvent<> &SubmitEvent()
		{
			return _submit_event;
		}

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
		/// @return
		///
		QString LeftPlaceholderText() const
		{
			return _range_submit.LeftPlaceholderText();
		}

		///
		/// @brief 设置左侧输入框在没有输入内容时显示的文本。
		///
		/// @param value
		///
		void SetLeftPlaceholderText(QString const &value)
		{
			_range_submit.SetLeftPlaceholderText(value);
		}

		///
		/// @brief 设置左侧输入框在没有输入内容时显示的文本。
		///
		/// @param value
		///
		void SetLeftPlaceholderText(std::string const &value)
		{
			_range_submit.SetLeftPlaceholderText(value);
		}

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
		/// @return
		///
		QString RightPlaceholderText() const
		{
			return _range_submit.RightPlaceholderText();
		}

		///
		/// @brief 设置右侧输入框在没有输入内容时显示的文本。
		///
		/// @param value
		///
		void SetRightPlaceholderText(QString const &value)
		{
			_range_submit.SetRightPlaceholderText(value);
		}

		///
		/// @brief 设置右侧输入框在没有输入内容时显示的文本。
		///
		/// @param value
		///
		void SetRightPlaceholderText(std::string const &value)
		{
			_range_submit.SetRightPlaceholderText(value);
		}

		///
		/// @brief 设置右侧输入框在没有输入内容时显示的文本。
		///
		/// @param value
		///
		void SetRightPlaceholderText(char const *value);

		///
		/// @brief 右侧输入框在没有输入内容时显示的文本。
		///
		/// @return
		///
		std::string RightPlaceholderTextStdString() const
		{
			return _range_submit.RightPlaceholderTextStdString();
		}

		/* #endregion */

		/* #region 输入框的文本 */

		///
		/// @brief 左侧输入框的文本。
		///
		/// @return
		///
		QString LeftText() const
		{
			return _range_submit.LeftText();
		}

		///
		/// @brief 设置左侧输入框的文本。
		///
		/// @param value
		///
		void SetLeftText(QString const &value)
		{
			_range_submit.SetLeftText(value);
		}

		///
		/// @brief 设置左侧输入框的文本。
		///
		/// @param value
		///
		void SetLeftText(std::string const &value)
		{
			_range_submit.SetLeftText(value);
		}

		///
		/// @brief 设置左侧输入框的文本。
		///
		/// @param value
		///
		void SetLeftText(char const *value)
		{
			_range_submit.SetLeftText(value);
		}

		///
		/// @brief 左侧输入框的文本。
		///
		/// @return
		///
		std::string LeftTextStdString() const
		{
			return _range_submit.LeftTextStdString();
		}

		///
		/// @brief 右侧输入框的文本。
		///
		/// @return
		///
		QString RightText() const
		{
			return _range_submit.RightText();
		}

		///
		/// @brief 设置左侧输入框的文本。
		///
		/// @param value
		///
		void SetRightText(QString const &value)
		{
			_range_submit.SetRightText(value);
		}

		///
		/// @brief 设置左侧输入框的文本。
		///
		/// @param value
		///
		void SetRightText(std::string const &value)
		{
			_range_submit.SetRightText(value);
		}

		///
		/// @brief 设置左侧输入框的文本。
		///
		/// @param value
		///
		void SetRightText(char const *value)
		{
			_range_submit.SetRightText(value);
		}

		///
		/// @brief 右侧输入框的文本。
		///
		/// @return
		///
		std::string RightTextStdString() const
		{
			return _range_submit.RightTextStdString();
		}

		/* #endregion */
	};
} // namespace widget
