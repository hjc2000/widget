#pragma once
#include "base/math/Size.h"
#include "base/string/define.h"
#include "qdialog.h"
#include "qwidget.h"
#include "widget/layout/Padding.h"
#include "widget/layout/VBoxLayout.h"
#include <memory>
#include <stdexcept>
#include <string>

namespace widget
{
	///
	/// @brief 关闭弹窗事件参数。
	///
	///
	class CloseDialogEventArgs
	{
	private:
		bool _should_close = true;

	public:
		constexpr bool ShouldClose() const
		{
			return _should_close;
		}

		constexpr void SetShouldClose(bool value)
		{
			_should_close = value;
		}
	};

	///
	/// @brief 对话框。
	///
	///
	class Dialog :
		private QDialog
	{
	private:
		widget::VBoxLayout _layout{this};
		std::shared_ptr<QWidget> _content;
		base::Size _size{1020, 720};

		///
		/// @brief 重写 QDialog 的关闭事件处理函数，转发到 OnClose 函数。
		///
		/// @param event
		///
		virtual void closeEvent(QCloseEvent *event) override
		{
			widget::CloseDialogEventArgs param;
			OnClose(param);
			if (param.ShouldClose())
			{
				event->accept();
			}
			else
			{
				event->ignore();
			}
		}

	protected:
		///
		/// @brief 窗口关闭时触发。
		///
		/// @param param
		///
		virtual void OnClose(widget::CloseDialogEventArgs &param)
		{
		}

	public:
		/* #region 构造函数 */

		///
		/// @brief 构造函数。
		///
		///
		Dialog() = default;

		///
		/// @brief 构造函数。
		///
		/// @param title 窗口标题。
		///
		Dialog(std::string const &title)
		{
			setWindowTitle(title.c_str());
		}

		///
		/// @brief 构造函数
		///
		/// @param title 弹窗标题。
		/// @param content 弹窗内容。
		///
		Dialog(std::string const &title, std::shared_ptr<QWidget> content)
		{
			setWindowTitle(title.c_str());
			SetContent(content);
		}

		/* #endregion */

		/* #region 属性 */

		///
		/// @brief 设置弹窗的内容。
		///
		/// @param content
		///
		void SetContent(std::shared_ptr<QWidget> content)
		{
			if (content == nullptr)
			{
				throw std::invalid_argument{CODE_POS_STR + "不能传入空指针。"};
			}

			_content = content;
			_layout.AddWidget(_content.get());
		}

		widget::Padding Padding() const
		{
			return _layout.Padding();
		}

		void SetPadding(widget::Padding const &value)
		{
			_layout.SetPadding(value);
		}

		/* #endregion */

		/* #region 展示弹窗 */

		///
		/// @brief 以模态方式展示弹窗。
		///
		///
		void ShowModal()
		{
			resize(_size.XSize(), _size.YSize());
			exec();
		}

		///
		/// @brief 以模态方式展示弹窗。
		///
		/// @param size 弹窗大小。
		///
		void ShowModal(base::Size const &size)
		{
			_size = size;
			resize(_size.XSize(), _size.YSize());
			exec();
		}

		/* #endregion */
	};

} // namespace widget
