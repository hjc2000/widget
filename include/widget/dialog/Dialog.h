#pragma once
#include "base/math/Size.h"
#include "qdialog.h"
#include "qwidget.h"
#include "widget/layout/Padding.h"
#include "widget/layout/VBoxLayout.h"
#include <memory>
#include <string>

namespace widget
{
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

	public:
		/* #region 构造函数 */

		///
		/// @brief 构造函数。
		///
		///
		Dialog();

		///
		/// @brief 构造函数。
		///
		/// @param title 窗口标题。
		///
		Dialog(std::string const &title);

		///
		/// @brief 构造函数
		///
		/// @param title 弹窗标题。
		/// @param content 弹窗内容。
		///
		Dialog(std::string const &title, std::shared_ptr<QWidget> content);

		/* #endregion */

		/* #region 属性 */

		///
		/// @brief 设置弹窗的内容。
		///
		/// @param content
		///
		void SetContent(std::shared_ptr<QWidget> content);

		widget::Padding Padding() const;
		void SetPadding(widget::Padding const &value);

		/* #endregion */

		/* #region 展示弹窗 */

		///
		/// @brief 以模态方式展示弹窗。
		///
		///
		void ShowModal();

		///
		/// @brief 以模态方式展示弹窗。
		///
		/// @param size 弹窗大小。
		///
		void ShowModal(base::Size const &size);

		/* #endregion */
	};
} // namespace widget
