#pragma once
#include <base/delegate/Delegate.h>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <string>

namespace widget
{
	class InputWidget :
		public QWidget
	{
	private:
		QHBoxLayout *_layout = new QHBoxLayout{this};
		QLineEdit *_line_edit = new QLineEdit{this};
		QPushButton *_button = new QPushButton{"提交", this};

#pragma region 事件
		base::Delegate<QString const &> _submit_event;
		base::Delegate<QString const &> _text_changed_event;
		base::Delegate<QString const &> _text_edited_event;
		base::Delegate<QString const &> _editing_finished;
#pragma endregion

		void InitializeLayout();
		void ConnectSignal();

	public:
		InputWidget(QWidget *parent);

		/// @brief 输入框在没有输入内容时显示的文本。
		/// @return
		QString PlaceholderText() const;

		/// @brief 设置：输入框在没有输入内容时显示的文本。
		/// @param value
		void SetPlaceholderText(QString const &value);

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

		/// @brief 获取按钮的文本。
		/// @return
		QString ButtonText() const;

		/// @brief 设置按钮的文本。
		/// @param value
		void SetButtonText(QString const &value) const;

#pragma region 事件
		/// @brief 提交。
		/// @note 提交按钮被点击或输入框中按下回车时触发此事件。
		/// @return
		base::IEvent<QString const &> &SubmitEvent();

		/// @brief 输入框中的文本改变。
		/// @note 无论改变的原因是什么，即不管是程序修改还是用户修改，都会触发。
		/// @return
		base::IEvent<QString const &> &TextChangedEvent();

		/// @brief 输入框中的文本被编辑。
		/// @note 只有用户编辑了输入框中的文本时才会触发，程序改变输入框的文本不会触发。
		/// @return
		base::IEvent<QString const &> &TextEditedEvent();

		/// @brief 编辑完成。
		/// @note 输入框中按下回车或输入框失去焦点时触发。
		/// @return
		base::IEvent<QString const &> &EditingFinishedEvent();
#pragma endregion
	};
} // namespace widget
