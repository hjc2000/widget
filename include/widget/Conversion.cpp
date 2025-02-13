#include "Conversion.h"

std::string widget::ToString(QString const &qstr)
{
	// 使用 toUtf8() 将 QString 转换为 QByteArray
	QByteArray utf8Bytes = qstr.toUtf8();

	// 将 QByteArray 转换为 std::string
	return std::string{utf8Bytes.constData(), static_cast<size_t>(utf8Bytes.size())};
}
