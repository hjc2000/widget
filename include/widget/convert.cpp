#include "convert.h"
#include "qcontainerfwd.h"

std::string std::to_string(QString const &qstr)
{
	// 使用 toUtf8() 将 QString 转换为 QByteArray
	QByteArray utf8Bytes = qstr.toUtf8();

	// 将 QByteArray 转换为 std::string
	return std::string{utf8Bytes.constData(), static_cast<size_t>(utf8Bytes.size())};
}

QString widget::ToQString(std::string const &str)
{
	return QString{str.c_str()};
}

QString widget::ToQString(char const *str)
{
	return QString{str};
}

widget::CheckState widget::ToCheckState(Qt::CheckState const q_check_state)
{
	switch (q_check_state)
	{
	case Qt::CheckState::Checked:
		{
			return widget::CheckState::Checked;
		}
	case Qt::CheckState::PartiallyChecked:
		{
			return widget::CheckState::PartiallyChecked;
		}
	default:
	case Qt::CheckState::Unchecked:
		{
			return widget::CheckState::Unchecked;
		}
	}
}

Qt::CheckState widget::ToQtCheckState(widget::CheckState const &check_state)
{
	switch (check_state)
	{
	case widget::CheckState::Checked:
		{
			return Qt::CheckState::Checked;
		}
	case widget::CheckState::PartiallyChecked:
		{
			return Qt::CheckState::PartiallyChecked;
		}
	default:
	case widget::CheckState::Unchecked:
		{
			return Qt::CheckState::Unchecked;
		}
	}
}
