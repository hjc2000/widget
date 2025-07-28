#pragma once
#include "base/delegate/Delegate.h"
#include "base/delegate/IEvent.h"
#include "base/string/define.h"
#include "QCheckBox"
#include "QWidget"
#include "widget/convert.h"
#include "widget/layout/HBoxLayout.h"
#include "widget/line-input-widget/CheckState.h"
#include <iostream>

namespace widget
{
	///
	/// @brief 选择框。
	///
	///
	class CheckBox final :
		public QWidget
	{
	private:
		std::shared_ptr<QCheckBox> _check_box;
		widget::HBoxLayout _layout{this};

		base::Delegate<> _check_state_changed_event;

		void ConnectSignals()
		{
			connect(_check_box.get(),
					&QCheckBox::checkStateChanged,
					[this](Qt::CheckState q_check_state)
					{
						try
						{
							_check_state_changed_event.Invoke();
						}
						catch (std::exception const &e)
						{
							std::cerr << CODE_POS_STR + e.what() << std::endl;
						}
						catch (...)
						{
							std::cerr << CODE_POS_STR + "发生了未知异常。" << std::endl;
						}
					});
		}

	public:
		CheckBox()
		{
			_check_box = std::shared_ptr<QCheckBox>{new QCheckBox{}};
			_layout.AddWidget(_check_box.get());

			ConnectSignals();
		}

		CheckBox(std::string const &text)
		{
			_check_box = std::shared_ptr<QCheckBox>{new QCheckBox{
				text.c_str(),
				nullptr,
			}};

			_layout.AddWidget(_check_box.get());

			ConnectSignals();
		}

		///
		/// @brief 选择状态。
		///
		/// @return
		///
		widget::CheckState CheckState() const
		{
			return widget::ToCheckState(_check_box->checkState());
		}

		///
		/// @brief 设置选择状态。
		///
		/// @param value
		///
		void SetCheckState(widget::CheckState value)
		{
			_check_box->setCheckState(widget::ToQtCheckState(value));
		}

		///
		/// @brief 选择状态改变事件。
		///
		/// @return
		///
		base::IEvent<> &CheckStateChangedEvent()
		{
			return _check_state_changed_event;
		}
	};

} // namespace widget
