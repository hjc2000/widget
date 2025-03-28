#include "Conversion.h"

std::string std::to_string(QString const &qstr)
{
	// 使用 toUtf8() 将 QString 转换为 QByteArray
	QByteArray utf8Bytes = qstr.toUtf8();

	// 将 QByteArray 转换为 std::string
	return std::string{utf8Bytes.constData(), static_cast<size_t>(utf8Bytes.size())};
}

QString &operator<<(QString &out, std::string const &in)
{
	out = in.c_str();
	return out;
}

widget::CheckState &operator<<(widget::CheckState &out, Qt::CheckState const &in)
{
	switch (in)
	{
	case Qt::CheckState::Checked:
		{
			out = widget::CheckState::Checked;
			break;
		}
	case Qt::CheckState::PartiallyChecked:
		{
			out = widget::CheckState::PartiallyChecked;
			break;
		}
	default:
	case Qt::CheckState::Unchecked:
		{
			out = widget::CheckState::Unchecked;
			break;
		}
	}

	return out;
}

Qt::CheckState &operator<<(Qt::CheckState &out, widget::CheckState const &in)
{
	switch (in)
	{
	case widget::CheckState::Checked:
		{
			out = Qt::CheckState::Checked;
			break;
		}
	case widget::CheckState::PartiallyChecked:
		{
			out = Qt::CheckState::PartiallyChecked;
			break;
		}
	default:
	case widget::CheckState::Unchecked:
		{
			out = Qt::CheckState::Unchecked;
			break;
		}
	}

	return out;
}
