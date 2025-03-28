#pragma once
#include "base/delegate/Delegate.h"
#include "qlineedit.h"
#include "widget/layout/HBoxLayout.h"

namespace widget
{
	///
	/// @brief 输入框控件。
	///
	///
	class Input :
		public QWidget
	{
	private:
		widget::HBoxLayout _layout{this};
		QLineEdit _line_edit{};

		void ConnectSignal();

		/* #region 对外提供事件 */

		base::Delegate<QString const &> _text_changed_event;
		base::Delegate<QString const &> _text_changing_finished_event;
		base::Delegate<QString const &> _text_edited_event;
		base::Delegate<QString const &> _text_editing_finished_event;

		/* #endregion */

	public:
		Input();

		/* #region PlaceholderText */

		///
		/// @brief 输入框在没有输入内容时显示的文本。
		///
		/// @return QString
		///
		QString PlaceholderText() const;

		///
		/// @brief 设置：输入框在没有输入内容时显示的文本。
		///
		/// @param value
		///
		void SetPlaceholderText(QString const &value);

		///
		/// @brief 设置：输入框在没有输入内容时显示的文本。
		///
		/// @param value
		///
		void SetPlaceholderText(std::string const &value);

		///
		/// @brief 设置：输入框在没有输入内容时显示的文本。
		///
		/// @param value
		///
		void SetPlaceholderText(char const *value);

		///
		/// @brief 输入框在没有输入内容时显示的文本。
		///
		/// @return std::string
		///
		std::string PlaceholderTextStdString() const;

		/* #endregion */

		/* #region Text */

		///
		/// @brief 编辑框中的文本。
		///
		/// @return QString
		///
		QString Text() const;

		///
		/// @brief 设置：编辑框中的文本。
		///
		/// @param value
		///
		void SetText(QString const &value);

		///
		/// @brief 设置：编辑框中的文本。
		///
		/// @param value
		///
		void SetText(std::string const &value);

		///
		/// @brief 设置：编辑框中的文本。
		///
		/// @param value
		///
		void SetText(char const *value);

		///
		/// @brief 编辑框中的文本。
		///
		/// @return std::string
		///
		std::string TextStdString() const;

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
		/// @return base::IEvent<QString const &>&
		///
		base::IEvent<QString const &> &TextChangedEvent();

		///
		/// @brief 输入框中的文本改变完成事件。
		///
		/// @note 无论改变的原因是什么，即不管是程序修改还是用户修改，都会触发。
		///
		/// @note 如果是程序引起的改变，调用完文本设置函数后触发。如果是用户编辑引起的改变，
		/// 将在用户按下回车或者让输入框失去焦点后触发。
		///
		/// @return base::IEvent<QString const &>&
		///
		base::IEvent<QString const &> &TextChangingFinishedEvent();

		///
		/// @brief 输入框中的文本正在被编辑事件。
		///
		/// @note 只有用户编辑了输入框中的文本时才会触发，程序改变输入框的文本不会触发。
		///
		/// @note 用户编辑时会实时触发，不需要按下回车或让输入框失去焦点。
		///
		/// @return base::IEvent<QString const &>&
		///
		base::IEvent<QString const &> &TextEditedEvent();

		///
		/// @brief 用户编辑完成事件。
		///
		/// @note 用户编辑完成后，在输入框中按下回车或输入框失去焦点时触发。
		///
		/// @return base::IEvent<QString const &>&
		///
		base::IEvent<QString const &> &TextEditingFinishedEvent();

		/* #endregion */

		///
		/// @brief 设置输入非法样式。
		///
		/// @param is_invalid 为 true 打开非法样式，为 false 恢复成正常样式。
		///
		void SetInvalidInputStyle(bool is_invalid);
	};
} // namespace widget
