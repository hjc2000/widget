#pragma once
#include <base/delegate/Delegate.h>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <widget/button/Button.h>
#include <widget/line-input-widget/Input.h>

namespace widget
{
	///
	/// @brief 提交组件。
	///
	/// @note 用来让用户提交一个输入信息。
	///
	class Submit :
		public QWidget
	{
	private:
		QHBoxLayout _layout{this};
		widget::Input _line_edit{};
		widget::Button _button{"提交"};

		base::Delegate<QString const &> _submit_event;

		void ConnectSignal();

	public:
		Submit();

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

		/* #endregion */

		/* #region 编辑框中的文本 */

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

		/* #endregion */

		/* #region 按钮的文本 */

		///
		/// @brief 按钮的文本。
		///
		/// @return QString
		///
		QString ButtonText() const;

		///
		/// @brief 设置按钮的文本。
		///
		/// @param value
		///
		void SetButtonText(QString const &value);

		///
		/// @brief 设置按钮的文本。
		///
		/// @param value
		///
		void SetButtonText(std::string const &value);

		///
		/// @brief 设置按钮的文本。
		///
		/// @param value
		///
		void SetButtonText(char const *value);
		/* #endregion */

		///
		/// @brief 提交事件。
		///
		/// @note 提交按钮被点击或输入框中按下回车时触发此事件。
		///
		/// @return base::IEvent<QString const &>&
		///
		base::IEvent<QString const &> &SubmitEvent();

		/* #region 提交按钮可见性 */

		///
		/// @brief 隐藏提交按钮。
		///
		///
		void HideSubmissionButton();

		///
		/// @brief 展示提交按钮。
		///
		///
		void ShowSubmissionButton();

		///
		/// @brief 提交按钮的可见性。
		///
		/// @return true
		/// @return false
		///
		bool SubmissionButtonVisibility() const;

		///
		/// @brief 设置提交按钮的可见性。
		///
		/// @note true 表示可见，false 表示不可见。
		///
		/// @param value
		///
		void SetSubmissionButtonVisibility(bool value);
		/* #endregion */
	};
} // namespace widget
