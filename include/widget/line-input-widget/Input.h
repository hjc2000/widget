#pragma once
#include "base/delegate/Delegate.h"
#include "base/IDisposable.h"
#include "qcoreapplication.h"
#include "qlineedit.h"
#include "widget/convert.h"
#include "widget/layout/HBoxLayout.h"
#include <vector>

namespace widget
{
	///
	/// @brief 输入框控件。
	///
	///
	class Input final :
		public QWidget,
		public base::IDisposable
	{
	private:
		bool _disposed = false;
		widget::HBoxLayout _layout{this};
		QLineEdit *_line_edit = new QLineEdit{};

		/* #region 对外提供事件 */

		base::Delegate<QString const &> _text_changed_event;
		base::Delegate<QString const &> _text_changing_finished_event;
		base::Delegate<QString const &> _text_edited_event;
		base::Delegate<QString const &> _text_editing_finished_event;

		/* #endregion */

		std::vector<QMetaObject::Connection> _connections;

		void ConnectSignal();

	public:
		Input()
		{
			_line_edit->setPlaceholderText("在此处输入内容...");
			_line_edit->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
			_layout.AddWidget(_line_edit);
			ConnectSignal();
		}

		~Input()
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

			_text_changed_event.Dispose();
			_text_changing_finished_event.Dispose();
			_text_edited_event.Dispose();
			_text_editing_finished_event.Dispose();

			for (QMetaObject::Connection &connection : _connections)
			{
				disconnect(connection);
			}

			QCoreApplication::removePostedEvents(this);
		}

		/* #region PlaceholderText */

		///
		/// @brief 输入框在没有输入内容时显示的文本。
		///
		/// @return
		///
		QString PlaceholderText() const
		{
			return _line_edit->placeholderText();
		}

		///
		/// @brief 设置：输入框在没有输入内容时显示的文本。
		///
		/// @param value
		///
		void SetPlaceholderText(QString const &value)
		{
			_line_edit->setPlaceholderText(value);
		}

		///
		/// @brief 设置：输入框在没有输入内容时显示的文本。
		///
		/// @param value
		///
		void SetPlaceholderText(std::string const &value)
		{
			SetPlaceholderText(QString{value.c_str()});
		}

		///
		/// @brief 设置：输入框在没有输入内容时显示的文本。
		///
		/// @param value
		///
		void SetPlaceholderText(char const *value)
		{
			SetPlaceholderText(QString{value});
		}

		///
		/// @brief 输入框在没有输入内容时显示的文本。
		///
		/// @return
		///
		std::string PlaceholderTextStdString() const
		{
			std::string ret = base::to_string(PlaceholderText());
			return ret;
		}

		/* #endregion */

		/* #region Text */

		///
		/// @brief 编辑框中的文本。
		///
		/// @return
		///
		QString Text() const
		{
			return _line_edit->text();
		}

		///
		/// @brief 设置：编辑框中的文本。
		///
		/// @param value
		///
		void SetText(QString const &value)
		{
			_line_edit->setText(value);

			try
			{
				_text_changing_finished_event.Invoke(_line_edit->text());
			}
			catch (std::exception const &e)
			{
			}
			catch (...)
			{
			}
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

		///
		/// @brief 编辑框中的文本。
		///
		/// @return
		///
		std::string TextStdString() const
		{
			std::string ret = base::to_string(Text());
			return ret;
		}

		/* #endregion */

		/* #region 对外提供事件 */

		///
		/// @brief 输入框中的文本正在改变事件。
		///
		/// @note 无论改变的原因是什么，即不管是程序修改还是用户修改，都会触发。
		///
		/// @note 如果是程序引起的改变，调用完文本设置函数后触发。如果是用户编辑引起的改变，
		/// 将在用户编辑每个字符时实时触发。
		///
		/// @return
		///
		base::IEvent<QString const &> &TextChangedEvent()
		{
			return _text_changed_event;
		}

		///
		/// @brief 输入框中的文本改变完成事件。
		///
		/// @note 无论改变的原因是什么，即不管是程序修改还是用户修改，都会触发。
		///
		/// @note 如果是程序引起的改变，调用完文本设置函数后触发。如果是用户编辑引起的改变，
		/// 将在用户按下回车或者让输入框失去焦点后触发。
		///
		/// @return
		///
		base::IEvent<QString const &> &TextChangingFinishedEvent()
		{
			return _text_changing_finished_event;
		}

		///
		/// @brief 输入框中的文本正在被编辑事件。
		///
		/// @note 只有用户编辑了输入框中的文本时才会触发，程序改变输入框的文本不会触发。
		///
		/// @note 用户编辑时会实时触发，不需要按下回车或让输入框失去焦点。
		///
		/// @return
		///
		base::IEvent<QString const &> &TextEditedEvent()
		{
			return _text_edited_event;
		}

		///
		/// @brief 用户编辑完成事件。
		///
		/// @note 用户编辑完成后，在输入框中按下回车或输入框失去焦点时触发。
		///
		/// @return
		///
		base::IEvent<QString const &> &TextEditingFinishedEvent()
		{
			return _text_editing_finished_event;
		}

		/* #endregion */

		///
		/// @brief 设置输入非法样式。
		///
		/// @param is_invalid 为 true 打开非法样式，为 false 恢复成正常样式。
		///
		void SetInvalidInputStyle(bool is_invalid)
		{
			if (is_invalid)
			{
				_line_edit->setStyleSheet("border: 2px solid red;");
			}
			else
			{
				// 恢复默认样式
				_line_edit->setStyleSheet("");
			}
		}
	};

} // namespace widget
