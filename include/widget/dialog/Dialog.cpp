#include "Dialog.h"
#include "base/string/define.h"
#include <stdexcept>

void widget::Dialog::closeEvent(QCloseEvent *event)
{
	CloseRequest request = OnClose();
	if (request == CloseRequest::DoNotClose)
	{
		event->ignore();
	}

	event->accept();
}

/* #region 构造函数 */

widget::Dialog::Dialog()
{
}

widget::Dialog::Dialog(std::string const &title)
{
	setWindowTitle(title.c_str());
}

widget::Dialog::Dialog(std::string const &title, std::shared_ptr<QWidget> content)
{
	setWindowTitle(title.c_str());
	SetContent(content);
}

/* #endregion */

/* #region 属性 */

void widget::Dialog::SetContent(std::shared_ptr<QWidget> content)
{
	if (content == nullptr)
	{
		throw std::invalid_argument{CODE_POS_STR + "不能传入空指针。"};
	}

	_content = content;
	_layout.AddWidget(_content.get());
}

widget::Padding widget::Dialog::Padding() const
{
	return _layout.Padding();
}

void widget::Dialog::SetPadding(widget::Padding const &value)
{
	_layout.SetPadding(value);
}

/* #endregion */

/* #region 展示弹窗 */

void widget::Dialog::ShowModal()
{
	resize(_size.XSize(), _size.YSize());
	exec();
}

void widget::Dialog::ShowModal(base::Size const &size)
{
	_size = size;
	resize(_size.XSize(), _size.YSize());
	exec();
}

/* #endregion */
