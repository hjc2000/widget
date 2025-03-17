#pragma once
#include "Input.h"
#include <base/delegate/Delegate.h>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <widget/button/Button.h>
#include <widget/pch.h>

namespace widget
{
	/**
	 * @brief 提交组件。
	 *
	 * @note 用来让用户提交一个输入信息。
	 */
	class Submit :
		public QWidget
	{
	private: // 控件
		QHBoxLayout _layout{this};
		widget::Input _line_edit{};
		widget::Button _button{"提交"};

	private:
		base::Delegate<QString const &> _submit_event;

		void ConnectSignal();

	public:
		Submit();

	public: // PlaceholderText
		/**
		 * @brief 输入框在没有输入内容时显示的文本。
		 *
		 * @return QString
		 */
		QString PlaceholderText() const;

		/**
		 * @brief Set the Placeholder Text object设置：输入框在没有输入内容时显示的文本。
		 *
		 * @param value
		 */
		void SetPlaceholderText(QString const &value);

	public: // Text
		/// @brief 编辑框中的文本。
		/// @return
		QString Text() const;

		/// @brief 设置：编辑框中的文本。
		/// @param value
		void SetText(QString const &value);

		/// @brief 设置：编辑框中的文本。
		/// @param value
		void SetText(std::string const &value);

		/// @brief 设置：编辑框中的文本。
		/// @param value
		void SetText(char const *value);

	public: // ButtonText
		/// @brief 获取按钮的文本。
		/// @return
		QString ButtonText() const;

		/// @brief 设置按钮的文本。
		/// @param value
		void SetButtonText(QString const &value);
		void SetButtonText(std::string const &value);
		void SetButtonText(char const *value);

	public: // 事件
		/// @brief 提交。
		/// @note 提交按钮被点击或输入框中按下回车时触发此事件。
		/// @return
		base::IEvent<QString const &> &SubmitEvent();

	public: // 提交按钮可见性
		/**
		 * @brief 隐藏提交按钮。
		 *
		 */
		void HideSubmissionButton();

		/**
		 * @brief 展示提交按钮。
		 *
		 */
		void ShowSubmissionButton();

		/**
		 * @brief 提交按钮的可见性。
		 *
		 * @return true 可见
		 * @return false 不可见
		 */
		bool SubmissionButtonVisibility() const;

		/**
		 * @brief 设置提交按钮的可见性。
		 *
		 * @note true 表示可见，false 表示不可见。
		 *
		 * @param value
		 */
		void SetSubmissionButtonVisibility(bool value);
	};
} // namespace widget
