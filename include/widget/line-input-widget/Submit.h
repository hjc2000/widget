#pragma once
#include "base/delegate/Delegate.h"
#include "QHBoxLayout"
#include "QLineEdit"
#include "QPushButton"
#include "widget/button/Button.h"
#include "widget/IndependentQWidget.h"
#include "widget/line-input-widget/Input.h"

namespace widget
{
	///
	/// @brief 提交组件。
	///
	/// @note 用来让用户提交一个输入信息。
	///
	class Submit :
		public widget::IndependentQWidget
	{
	private:
		QHBoxLayout _layout{this};
		widget::Input _line_edit{};
		widget::Button _button{"提交"};

		base::Delegate<QString const &> _submit_event;

		void ConnectSignal()
		{
			_button.ClickedEvent().Subscribe(
				[this]()
				{
					try
					{
						_submit_event.Invoke(_line_edit.Text());
					}
					catch (std::exception const &e)
					{
					}
					catch (...)
					{
					}
				});

			_line_edit.TextChangingFinishedEvent().Subscribe(
				[this](QString const &text)
				{
					try
					{
						_submit_event.Invoke(_line_edit.Text());
					}
					catch (std::exception const &e)
					{
					}
					catch (...)
					{
					}
				});
		}

	public:
		Submit()
		{
			{
				setAutoFillBackground(true);
				QPalette temp_palette = palette();
				temp_palette.setColor(QPalette::Window, QColor{240, 240, 240});
				setPalette(temp_palette);
			}

			{
				// 将控件添加到布局中
				_layout.addWidget(&_line_edit);
				_layout.addWidget(&_button);

				// 控件之间的间距。在这里就是设置输入框和提交按钮之间的间距。
				_layout.setSpacing(10);

				// 布局内的内容区域与布局边框的间距。实际上相当于网页中的盒子内边距。
				_layout.setContentsMargins(0, 0, 0, 0);
			}

			ConnectSignal();
		}

		/* #region PlaceholderText */

		///
		/// @brief 输入框在没有输入内容时显示的文本。
		///
		/// @return
		///
		QString PlaceholderText() const
		{
			return _line_edit.PlaceholderText();
		}

		///
		/// @brief 设置：输入框在没有输入内容时显示的文本。
		///
		/// @param value
		///
		void SetPlaceholderText(QString const &value)
		{
			_line_edit.SetPlaceholderText(value);
		}

		/* #endregion */

		/* #region 编辑框中的文本 */

		///
		/// @brief 编辑框中的文本。
		///
		/// @return
		///
		QString Text() const
		{
			return _line_edit.Text();
		}

		///
		/// @brief 设置：编辑框中的文本。
		///
		/// @param value
		///
		void SetText(QString const &value)
		{
			_line_edit.SetText(value);
		}

		///
		/// @brief 设置：编辑框中的文本。
		///
		/// @param value
		///
		void SetText(std::string const &value)
		{
			SetText(QString{value.c_str()});
		}

		///
		/// @brief 设置：编辑框中的文本。
		///
		/// @param value
		///
		void SetText(char const *value)
		{
			SetText(QString{value});
		}

		/* #endregion */

		/* #region 按钮的文本 */

		///
		/// @brief 按钮的文本。
		///
		/// @return
		///
		QString ButtonText() const
		{
			return _button.text();
		}

		///
		/// @brief 设置按钮的文本。
		///
		/// @param value
		///
		void SetButtonText(QString const &value)
		{
			_button.setText(value);
		}

		///
		/// @brief 设置按钮的文本。
		///
		/// @param value
		///
		void SetButtonText(std::string const &value)
		{
			SetButtonText(QString{value.c_str()});
		}

		///
		/// @brief 设置按钮的文本。
		///
		/// @param value
		///
		void SetButtonText(char const *value)
		{
			SetButtonText(QString{value});
		}

		/* #endregion */

		///
		/// @brief 提交事件。
		///
		/// @note 提交按钮被点击或输入框中按下回车时触发此事件。
		///
		/// @return
		///
		base::IEvent<QString const &> &SubmitEvent()
		{
			return _submit_event;
		}

		/* #region 提交按钮可见性 */

		///
		/// @brief 隐藏提交按钮。
		///
		///
		void HideSubmissionButton()
		{
			_button.hide();
		}

		///
		/// @brief 展示提交按钮。
		///
		///
		void ShowSubmissionButton()
		{
			_button.show();
		}

		///
		/// @brief 提交按钮的可见性。
		///
		/// @return
		///
		bool SubmissionButtonVisibility() const
		{
			return !_button.isHidden();
		}

		///
		/// @brief 设置提交按钮的可见性。
		///
		/// @note true 表示可见，false 表示不可见。
		///
		/// @param value
		///
		void SetSubmissionButtonVisibility(bool value)
		{
			if (SubmissionButtonVisibility())
			{
				HideSubmissionButton();
			}
			else
			{
				ShowSubmissionButton();
			}
		}

		/* #endregion */
	};

} // namespace widget
