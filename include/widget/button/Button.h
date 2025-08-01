#pragma once
#include "base/delegate/Delegate.h"
#include "base/IDisposable.h"
#include "base/string/define.h"
#include "qcoreapplication.h"
#include "QPushButton"
#include "widget/convert.h"
#include <iostream>
#include <string>
#include <vector>

namespace widget
{
	///
	/// @brief 按钮。
	///
	///
	class Button final :
		public QPushButton,
		public base::IDisposable
	{
	private:
		///
		/// @brief 触发 enter 事件前的样式。在 enter 事件处理函数的一开始就记录到本字段中。
		///
		///
		QPalette _palette_before_enter_event;

		///
		/// @brief 触发 pressed 事件前的样式。在 pressed 事件处理函数地一开始就记录到本字段中。
		///
		///
		QPalette _palette_before_pressed_event;

		bool _disposed = false;

		std::vector<QMetaObject::Connection> _connections;

		/* #region 对外提供事件 */

		base::Delegate<> _clicked_event;
		base::Delegate<> _pressed_event;
		base::Delegate<> _released_event;
		base::Delegate<> _enter_event;
		base::Delegate<> _leave_event;

		/* #endregion */

		/* #region 本类的事件处理函数 */

		virtual void enterEvent(QEnterEvent *event) override
		{
			_palette_before_enter_event = palette();

			QPushButton::enterEvent(event);
			QPalette temp_palette = palette();
			temp_palette.setColor(QPalette::Button, QColor{150, 190, 230});
			setPalette(temp_palette);

			try
			{
				_enter_event.Invoke();
			}
			catch (std::exception const &e)
			{
				std::cerr << CODE_POS_STR + e.what() << std::endl;
			}
			catch (...)
			{
			}
		}

		virtual void leaveEvent(QEvent *event) override
		{
			QPushButton::leaveEvent(event);
			setPalette(_palette_before_enter_event);

			try
			{
				_leave_event.Invoke();
			}
			catch (std::exception const &e)
			{
				std::cerr << CODE_POS_STR + e.what() << std::endl;
			}
			catch (...)
			{
			}
		}

		void OnClicked()
		{
			try
			{
				_clicked_event.Invoke();
			}
			catch (std::exception const &e)
			{
				std::cerr << CODE_POS_STR + e.what() << std::endl;
			}
			catch (...)
			{
			}
		}

		void OnPressed()
		{
			_palette_before_pressed_event = palette();

			QPalette temp_palette = palette();
			temp_palette.setColor(QPalette::Button, QColor{100, 150, 255});
			setPalette(temp_palette);

			try
			{
				_pressed_event.Invoke();
			}
			catch (std::exception const &e)
			{
				std::cerr << CODE_POS_STR + e.what() << std::endl;
			}
			catch (...)
			{
			}
		}

		void OnReleased()
		{
			setPalette(_palette_before_pressed_event);

			try
			{
				_released_event.Invoke();
			}
			catch (std::exception const &e)
			{
				std::cerr << CODE_POS_STR + e.what() << std::endl;
			}
			catch (...)
			{
			}
		}

		/* #endregion */

		void ConnectSignal()
		{
			QMetaObject::Connection connection;

			connection = connect(this,
								 &QPushButton::clicked,
								 [this]()
								 {
									 OnClicked();
								 });

			_connections.push_back(connection);

			connection = connect(this,
								 &QPushButton::pressed,
								 [this]()
								 {
									 OnPressed();
								 });

			_connections.push_back(connection);

			connection = connect(this,
								 &QPushButton::released,
								 [this]()
								 {
									 OnReleased();
								 });

			_connections.push_back(connection);
		}

	public:
		/* #region 构造函数 */

		Button()
		{
			SetText("按钮");
			setAutoFillBackground(true);

			// 按钮大小由内容决定，且固定大小。
			setSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);

			{
				QPalette temp_palette = palette();
				temp_palette.setColor(QPalette::Button, QColor{255, 255, 255});
				setPalette(temp_palette);
			}

			ConnectSignal();
		}

		///
		/// @brief
		///
		/// @param text 按钮显示的文本。
		///
		Button(QString const &text)
			: Button()
		{
			SetText(text);
		}

		///
		/// @brief
		///
		/// @param text 按钮显示的文本。
		///
		Button(std::string const &text)
			: widget::Button(widget::ToQString(text))
		{
		}

		///
		/// @brief
		///
		/// @param text 按钮显示的文本。
		///
		Button(char const *text)
			: widget::Button(widget::ToQString(text))
		{
		}

		/* #endregion */

		~Button()
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

			_clicked_event.Dispose();
			_pressed_event.Dispose();
			_released_event.Dispose();
			_enter_event.Dispose();
			_leave_event.Dispose();

			for (QMetaObject::Connection &connection : _connections)
			{
				disconnect(connection);
			}

			QCoreApplication::removePostedEvents(this);
		}

		/* #region 对外提供事件 */

		///
		/// @brief 按钮点击事件。
		///
		/// @return
		///
		base::IEvent<> &ClickedEvent()
		{
			return _clicked_event;
		}

		///
		/// @brief 鼠标按钮按下，没有释放时触发的事件。
		///
		/// @return
		///
		base::IEvent<> &PressedEvent()
		{
			return _pressed_event;
		}

		///
		/// @brief 鼠标按钮从按下状态变成释放状态时触发的事件。
		///
		/// @return
		///
		base::IEvent<> &ReleasedEvent()
		{
			return _released_event;
		}

		///
		/// @brief 鼠标进入按钮时触发的事件。
		///
		/// @return
		///
		base::IEvent<> &EnterEvent()
		{
			return _enter_event;
		}

		///
		/// @brief 鼠标离开按钮时触发的事件。
		///
		/// @return
		///
		base::IEvent<> &LeaveEvent()
		{
			return _leave_event;
		}

		/* #endregion */

		/* #region 文本 */

		///
		/// @brief 按钮的文本。
		///
		/// @return QString
		///
		QString Text() const
		{
			return text();
		}

		///
		/// @brief 设置按钮的文本。
		///
		/// @param value
		///
		void SetText(QString const &value)
		{
			setText(value);
		}

		///
		/// @brief 设置按钮的文本。
		///
		/// @param value
		///
		void SetText(std::string const &value)
		{
			SetText(QString{value.c_str()});
		}

		///
		/// @brief 设置按钮的文本。
		///
		/// @param value
		///
		void SetText(char const *value)
		{
			SetText(QString{value});
		}

		/* #endregion */
	};

} // namespace widget
