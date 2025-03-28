#pragma once
#include "base/math/Size.h"
#include "qdialog.h"
#include <string>

namespace widget
{
	class Dialog :
		public QDialog
	{
	public:
		Dialog();

		///
		/// @brief 构造函数。
		///
		/// @param title 窗口标题。
		///
		Dialog(std::string const &title);

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
	};
} // namespace widget
