#pragma once
#include "base/delegate/IEvent.h"
#include "base/IDisposable.h"
#include "base/math/interval/ClosedInterval.h"
#include "base/string/define.h"
#include "widget/layout/VBoxLayout.h"
#include "widget/line-input-widget/RangeSubmit.h"
#include <cstdint>
#include <iostream>
#include <memory>

namespace widget
{
	///
	/// @brief 整型范围提交控件。
	///
	class IntRangeSubmit final :
		public QWidget,
		public base::IDisposable
	{
	private:
		bool _disposed = false;
		widget::VBoxLayout _layout{this};
		std::shared_ptr<widget::RangeSubmit> _range_submit{new widget::RangeSubmit{}};

		int64_t _min = INT64_MIN;
		int64_t _max = INT64_MAX;

		int64_t _left_value = 0;
		int64_t _right_value = 0;

		base::Delegate<> _submit_event;

		bool TryParseLeftValue(int64_t &out);

		bool TryParseRightValue(int64_t &out);

		void CheckLeftRightValues(int64_t left_value, int64_t right_value)
		{
			if (left_value > right_value)
			{
				std::cerr << CODE_POS_STR + "左侧值不能大于右侧值。" << std::endl;
				SetLeftInvalidInputStyle(true);
				SetRightInvalidInputStyle(true);
				return;
			}

			if (left_value < _min)
			{
				std::cerr << CODE_POS_STR + "左侧值不能小于最小值。" << std::endl;
				SetLeftInvalidInputStyle(true);
				return;
			}

			if (right_value > _max)
			{
				std::cerr << CODE_POS_STR + "右侧值不能大于最大值。" << std::endl;
				SetRightInvalidInputStyle(true);
				return;
			}

			// 数据合法
			_left_value = left_value;
			_right_value = right_value;
			SetLeftInvalidInputStyle(false);
			SetRightInvalidInputStyle(false);
		}

		void OnSubmit()
		{
			int64_t left_value = 0;
			int64_t right_value = 0;
			bool parse_left_value_result = TryParseLeftValue(left_value);
			bool parse_right_value_result = TryParseRightValue(right_value);

			if (!(parse_left_value_result && parse_right_value_result))
			{
				return;
			}

			CheckLeftRightValues(left_value, right_value);

			try
			{
				_submit_event.Invoke();
			}
			catch (std::exception const &e)
			{
				std::cerr << CODE_POS_STR + e.what() << std::endl;
			}
			catch (...)
			{
				std::cerr << CODE_POS_STR + "发生了未知错误" << std::endl;
			}
		}

	public:
		IntRangeSubmit()
		{
			setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
			_layout.AddWidget(_range_submit);

			_range_submit->SubmitEvent().Subscribe([this]()
												   {
													   OnSubmit();
												   });

			_range_submit->SetLeftText(std::to_string(_left_value));
			_range_submit->SetRightText(std::to_string(_right_value));
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

		~IntRangeSubmit()
		{
			Dispose();
		}

		///
		/// @brief 处置对象，让对象准备好结束生命周期。类似于进入 “准备后事” 的状态。
		///
		/// @note 注意，对象并不是析构了，并不是完全无法访问，它仍然允许访问，仍然能执行一些
		/// 符合 “准备后事” 的工作。
		///
		virtual void Dispose() override
		{
			if (_disposed)
			{
				return;
			}

			_disposed = true;

			_range_submit->Dispose();
			_submit_event.Dispose();
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
		void SetLeftInvalidInputStyle(bool is_invalid)
		{
			_range_submit->SetLeftInvalidInputStyle(is_invalid);
		}

		///
		/// @brief 设置右边输入框的输入非法样式。
		///
		/// @param is_invalid 为 true 打开非法样式，为 false 恢复成正常样式。
		///
		void SetRightInvalidInputStyle(bool is_invalid)
		{
			_range_submit->SetRightInvalidInputStyle(is_invalid);
		}

		/* #endregion */

		/* #region PlaceholderText */

		///
		/// @brief 左侧输入框在没有输入内容时显示的文本。
		///
		/// @return
		///
		QString LeftPlaceholderText() const
		{
			return _range_submit->LeftPlaceholderText();
		}

		///
		/// @brief 设置左侧输入框在没有输入内容时显示的文本。
		///
		/// @param value
		///
		void SetLeftPlaceholderText(QString const &value)
		{
			_range_submit->SetLeftPlaceholderText(value);
		}

		///
		/// @brief 设置左侧输入框在没有输入内容时显示的文本。
		///
		/// @param value
		///
		void SetLeftPlaceholderText(std::string const &value)
		{
			_range_submit->SetLeftPlaceholderText(value);
		}

		///
		/// @brief 设置左侧输入框在没有输入内容时显示的文本。
		///
		/// @param value
		///
		void SetLeftPlaceholderText(char const *value)
		{
			_range_submit->SetLeftPlaceholderText(value);
		}

		///
		/// @brief 左侧输入框在没有输入内容时显示的文本。
		///
		/// @return std::string
		///
		std::string LeftPlaceholderTextStdString() const
		{
			return _range_submit->LeftPlaceholderTextStdString();
		}

		///
		/// @brief 右侧输入框在没有输入内容时显示的文本。
		///
		/// @return
		///
		QString RightPlaceholderText() const
		{
			return _range_submit->RightPlaceholderText();
		}

		///
		/// @brief 设置右侧输入框在没有输入内容时显示的文本。
		///
		/// @param value
		///
		void SetRightPlaceholderText(QString const &value)
		{
			_range_submit->SetRightPlaceholderText(value);
		}

		///
		/// @brief 设置右侧输入框在没有输入内容时显示的文本。
		///
		/// @param value
		///
		void SetRightPlaceholderText(std::string const &value)
		{
			_range_submit->SetRightPlaceholderText(value);
		}

		///
		/// @brief 设置右侧输入框在没有输入内容时显示的文本。
		///
		/// @param value
		///
		void SetRightPlaceholderText(char const *value)
		{
			_range_submit->SetRightPlaceholderText(value);
		}

		///
		/// @brief 右侧输入框在没有输入内容时显示的文本。
		///
		/// @return
		///
		std::string RightPlaceholderTextStdString() const
		{
			return _range_submit->RightPlaceholderTextStdString();
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
			return _range_submit->LeftText();
		}

		///
		/// @brief 设置左侧输入框的文本。
		///
		/// @param value
		///
		void SetLeftText(QString const &value)
		{
			_range_submit->SetLeftText(value);
		}

		///
		/// @brief 设置左侧输入框的文本。
		///
		/// @param value
		///
		void SetLeftText(std::string const &value)
		{
			_range_submit->SetLeftText(value);
		}

		///
		/// @brief 设置左侧输入框的文本。
		///
		/// @param value
		///
		void SetLeftText(char const *value)
		{
			_range_submit->SetLeftText(value);
		}

		///
		/// @brief 左侧输入框的文本。
		///
		/// @return
		///
		std::string LeftTextStdString() const
		{
			return _range_submit->LeftTextStdString();
		}

		///
		/// @brief 右侧输入框的文本。
		///
		/// @return
		///
		QString RightText() const
		{
			return _range_submit->RightText();
		}

		///
		/// @brief 设置左侧输入框的文本。
		///
		/// @param value
		///
		void SetRightText(QString const &value)
		{
			_range_submit->SetRightText(value);
		}

		///
		/// @brief 设置左侧输入框的文本。
		///
		/// @param value
		///
		void SetRightText(std::string const &value)
		{
			_range_submit->SetRightText(value);
		}

		///
		/// @brief 设置左侧输入框的文本。
		///
		/// @param value
		///
		void SetRightText(char const *value)
		{
			_range_submit->SetRightText(value);
		}

		///
		/// @brief 右侧输入框的文本。
		///
		/// @return
		///
		std::string RightTextStdString() const
		{
			return _range_submit->RightTextStdString();
		}

		/* #endregion */
	};

} // namespace widget
