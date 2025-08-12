#pragma once
#include "base/delegate/Delegate.h"
#include "base/delegate/IEvent.h"
#include "base/IDisposable.h"
#include "qcombobox.h"
#include "qcoreapplication.h"
#include "qwidget.h"
#include "widget/convert.h"
#include "widget/layout/VBoxLayout.h"
#include <initializer_list>
#include <string>
#include <vector>

namespace widget
{
	///
	/// @brief 下拉选择框组件。
	///
	///
	class ComboBox :
		public QWidget,
		public base::IDisposable
	{
	private:
		bool _disposed = false;
		widget::VBoxLayout _layout{this};
		QComboBox _combo_box{};
		std::vector<QMetaObject::Connection> _connections{};

		base::Delegate<int> _current_index_changed{};
		base::Delegate<std::string const &> _current_text_changed{};

		void ConnectSignals();

	public:
		ComboBox()
		{
			_layout.AddWidget(&_combo_box);
			_combo_box.setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
			ConnectSignals();
		}

		ComboBox(std::initializer_list<std::string> const &items)
			: ComboBox()
		{
			for (std::string const &item : items)
			{
				AddItem(item);
			}
		}

		~ComboBox()
		{
			Dispose();
			_combo_box.setParent(nullptr);
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

			_current_index_changed.Dispose();
			_current_text_changed.Dispose();

			for (QMetaObject::Connection &connection : _connections)
			{
				disconnect(connection);
			}

			QCoreApplication::removePostedEvents(this);
		}

		/* #region AddItem */

		void AddItem(QString const &item)
		{
			_combo_box.addItem(item);
		}

		void AddItem(std::string const &item)
		{
			AddItem(widget::ToQString(item));
		}

		void AddItem(char const *item)
		{
			AddItem(widget::ToQString(item));
		}

		/* #endregion */

		///
		/// @brief 当前索引改变事件。
		///
		/// @return
		///
		base::IEvent<int> &CurrentIndexChangedEvent()
		{
			return _current_index_changed;
		}

		///
		/// @brief 当前文本改变事件。
		///
		/// @return
		///
		base::IEvent<std::string const &> &CurrentTextChangedEvent()
		{
			return _current_text_changed;
		}

		///
		/// @brief 当前索引。
		///
		/// @return
		///
		int CurrentIndex() const
		{
			return _combo_box.currentIndex();
		}

		///
		/// @brief 设置当前索引。
		///
		/// @param index
		///
		void SetCurrentIndex(int index)
		{
			if (_combo_box.currentIndex() != index)
			{
				_combo_box.setCurrentIndex(index);
			}
		}

		///
		/// @brief 设置当前文本。
		///
		/// @return
		///
		std::string CurrentText() const
		{
			return base::to_string(_combo_box.currentText());
		}

		///
		/// @brief 当前文本。
		///
		/// @param value
		///
		void SetCurrentText(std::string const &value)
		{
			if (CurrentText() != value)
			{
				_combo_box.setCurrentText(widget::ToQString(value));
			}
		}
	};

} // namespace widget
