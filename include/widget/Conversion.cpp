#include "Conversion.h"

std::string widget::ToString(QString const &qstr)
{
	// 使用 toUtf8() 将 QString 转换为 QByteArray
	QByteArray utf8Bytes = qstr.toUtf8();

	// 将 QByteArray 转换为 std::string
	return std::string{utf8Bytes.constData(), static_cast<size_t>(utf8Bytes.size())};
}

std::string &operator<<(std::string &out, QString const &in)
{
	out = widget::ToString(in);
	return out;
}

QString &operator<<(QString &out, std::string const &in)
{
	out = in.c_str();
	return out;
}
