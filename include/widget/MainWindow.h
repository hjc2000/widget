#pragma once
#include "box/VBox.h"
#include "qcheckbox.h"
#include "qwindowdefs.h"
#include <base/delegate/Delegate.h>
#include <memory>
#include <QCheckBox >
#include <QDateTimeEdit>
#include <QMainWindow>
#include <QVBoxLayout>
#include <widget/box/HBox.h>
#include <widget/box/VBox.h>
#include <widget/layout/FormTableLayout.h>
#include <widget/layout/GridLayout.h>
#include <widget/layout/VBoxLayout.h>
#include <widget/line-input-widget/DateTimeRangeSubmit.h>
#include <widget/line-input-widget/RangeSubmit.h>
#include <widget/line-input-widget/Submit.h>

namespace widget
{
	/**
	 * @brief 主窗口。
	 *
	 */
	class MainWindow :
		public QMainWindow
	{
	private:
		std::shared_ptr<widget::VBox> _vbox{
			new widget::VBox{
				std::shared_ptr<widget::HBox>{
					new widget::HBox{
						std::shared_ptr<widget::RangeSubmit>{
							new widget::RangeSubmit{},
						},
						std::shared_ptr<QCheckBox>{
							new QCheckBox{"选择框"},
						},
					},
				},
				std::shared_ptr<widget::HBox>{
					new widget::HBox{
						std::shared_ptr<widget::RangeSubmit>{
							new widget::RangeSubmit{},
						},
						std::shared_ptr<QCheckBox>{
							new QCheckBox{"选择框"},
						},
						std::shared_ptr<widget::VBox>{
							new widget::VBox{
								std::shared_ptr<widget::HBox>{
									new widget::HBox{
										std::shared_ptr<widget::RangeSubmit>{
											new widget::RangeSubmit{},
										},
										std::shared_ptr<QCheckBox>{
											new QCheckBox{"选择框"},
										},
									},
								},
								std::shared_ptr<widget::HBox>{
									new widget::HBox{
										std::shared_ptr<widget::RangeSubmit>{
											new widget::RangeSubmit{},
										},
										std::shared_ptr<QCheckBox>{
											new QCheckBox{"选择框"},
										},
									},
								},
							},
						},
					},
				},
			},
		};

	public:
		/**
		 * @brief Construct a new Main Window object
		 *
		 */
		MainWindow();
	};
} // namespace widget
