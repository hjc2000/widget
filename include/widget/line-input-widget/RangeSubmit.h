#pragma once
#include "base/IDisposable.h"
#include "qlabel.h"
#include "widget/box/GridBox.h"
#include "widget/box/GridBoxItem.h"
#include "widget/convert.h"
#include "widget/IndependentQWidget.h"
#include "widget/layout/VBoxLayout.h"
#include "widget/line-input-widget/Input.h"
#include <memory>

namespace widget
{
	///
	/// @brief 提交一个范围。
	///
	/// @note 分成左右 2 个输入框，2 个输入框中间一条短横线，表示 从...到... ，右侧一个提交按钮，
	/// 点击后就是确认提交。
	///
	class RangeSubmit final :
		public widget::IndependentQWidget,
		public base::IDisposable
	{
	private:
		bool _disposed = false;
		widget::VBoxLayout _layout{this};

		std::shared_ptr<widget::Input> _left_edit{new widget::Input{}};
		std::shared_ptr<QLabel> _label{new QLabel{"-"}};
		std::shared_ptr<widget::Input> _right_edit{new widget::Input{}};

		std::shared_ptr<widget::GridBox> _grid_box{new widget::GridBox{
			widget::GridBoxItem{0, 0, _left_edit},
			widget::GridBoxItem{0, 1, _label},
			widget::GridBoxItem{0, 2, _right_edit},
		}};

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
		RangeSubmit()
		{
			setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
			_layout.AddWidget(_grid_box.get());

			_left_edit->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
			_label->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
			_right_edit->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);

			_grid_box->SetColumnStretch(0, 1);
			_grid_box->SetColumnStretch(1, 0);
			_grid_box->SetColumnStretch(2, 1);

			{
				setAutoFillBackground(true);
				QPalette temp_palette = palette();
				temp_palette.setColor(QPalette::Window, QColor{240, 240, 240});
				setPalette(temp_palette);
			}

			{
				// 订阅事件
				_left_edit->TextChangingFinishedEvent().Subscribe([this](QString const &text)
																  {
																	  _submit_event.Invoke();
																  });

				_right_edit->TextChangingFinishedEvent().Subscribe([this](QString const &text)
																   {
																	   _submit_event.Invoke();
																   });
			}
		}

		~RangeSubmit()
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

			_left_edit->Dispose();
			_right_edit->Dispose();
			_submit_event.Dispose();
		}

		/* #region PlaceholderText */

		///
		/// @brief 左侧输入框在没有输入内容时显示的文本。
		///
		/// @return
		///
		QString LeftPlaceholderText() const
		{
			return _left_edit->PlaceholderText();
		}

		///
		/// @brief 设置左侧输入框在没有输入内容时显示的文本。
		///
		/// @param value
		///
		void SetLeftPlaceholderText(QString const &value)
		{
			_left_edit->SetPlaceholderText(value);
		}

		///
		/// @brief 设置左侧输入框在没有输入内容时显示的文本。
		///
		/// @param value
		///
		void SetLeftPlaceholderText(std::string const &value)
		{
			_left_edit->SetPlaceholderText(value.c_str());
		}

		///
		/// @brief 设置左侧输入框在没有输入内容时显示的文本。
		///
		/// @param value
		///
		void SetLeftPlaceholderText(char const *value)
		{
			_left_edit->SetPlaceholderText(value);
		}

		///
		/// @brief 左侧输入框在没有输入内容时显示的文本。
		///
		/// @return
		///
		std::string LeftPlaceholderTextStdString() const
		{
			return base::to_string(LeftPlaceholderText());
		}

		///
		/// @brief 右侧输入框在没有输入内容时显示的文本。
		///
		/// @return
		///
		QString RightPlaceholderText() const
		{
			return _right_edit->PlaceholderText();
		}

		///
		/// @brief 设置右侧输入框在没有输入内容时显示的文本。
		///
		/// @param value
		///
		void SetRightPlaceholderText(QString const &value)
		{
			_right_edit->SetPlaceholderText(value);
		}

		///
		/// @brief 设置右侧输入框在没有输入内容时显示的文本。
		///
		/// @param value
		///
		void SetRightPlaceholderText(std::string const &value)
		{
			_right_edit->SetPlaceholderText(value.c_str());
		}

		///
		/// @brief 设置右侧输入框在没有输入内容时显示的文本。
		///
		/// @param value
		///
		void SetRightPlaceholderText(char const *value)
		{
			_right_edit->SetPlaceholderText(value);
		}

		///
		/// @brief 右侧输入框在没有输入内容时显示的文本。
		///
		/// @param value
		///
		std::string RightPlaceholderTextStdString() const
		{
			return base::to_string(RightPlaceholderText());
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
			return _left_edit->Text();
		}

		///
		/// @brief 设置左侧输入框的文本。
		///
		/// @param value
		///
		void SetLeftText(QString const &value)
		{
			_left_edit->SetText(value);
		}

		///
		/// @brief 设置左侧输入框的文本。
		///
		/// @param value
		///
		void SetLeftText(std::string const &value)
		{
			_left_edit->SetText(value);
		}

		///
		/// @brief 设置左侧输入框的文本。
		///
		/// @param value
		///
		void SetLeftText(char const *value)
		{
			_left_edit->SetText(value);
		}

		///
		/// @brief 左侧输入框的文本。
		///
		/// @return
		///
		std::string LeftTextStdString() const
		{
			return base::to_string(LeftText());
		}

		///
		/// @brief 右侧输入框的文本。
		///
		/// @return
		///
		QString RightText() const
		{
			return _right_edit->Text();
		}

		///
		/// @brief 设置右侧输入框的文本。
		///
		/// @param value
		///
		void SetRightText(QString const &value)
		{
			_right_edit->SetText(value);
		}

		///
		/// @brief 设置右侧输入框的文本。
		///
		/// @param value
		///
		void SetRightText(std::string const &value)
		{
			_right_edit->SetText(value);
		}

		///
		/// @brief 设置右侧输入框的文本。
		///
		/// @param value
		///
		void SetRightText(char const *value)
		{
			_right_edit->SetText(value);
		}

		///
		/// @brief 右侧输入框的文本。
		///
		/// @return
		///
		std::string RightTextStdString() const
		{
			return base::to_string(RightText());
		}

		/* #endregion */

		///
		/// @brief 提交数据时触发的事件。
		///
		/// @note 触发条件
		/// 	@li 用户在左右 2 个输入框中的任意一个按下回车。
		/// 	@li 用户在左右 2 个输入框中的任意一个编辑后让输入框失去焦点。
		///
		/// @return
		///
		base::IEvent<> &SubmitEvent()
		{
			return _submit_event;
		}

		///
		/// @brief 设置左边输入框的输入非法样式。
		///
		/// @param is_invalid 为 true 打开非法样式，为 false 恢复成正常样式。
		///
		void SetLeftInvalidInputStyle(bool is_invalid)
		{
			_left_edit->SetInvalidInputStyle(is_invalid);
		}

		///
		/// @brief 设置右边输入框的输入非法样式。
		///
		/// @param is_invalid 为 true 打开非法样式，为 false 恢复成正常样式。
		///
		void SetRightInvalidInputStyle(bool is_invalid)
		{
			_right_edit->SetInvalidInputStyle(is_invalid);
		}
	};

} // namespace widget
