#include "XmlSerializable.h" // IWYU pragma: keep
#include "widget/convert.h"

std::string widget::XmlSerializable::ToXmlString(int indent) const
{
	QDomDocument doc;
	doc.appendChild(ToXml(doc));
	QString qstr = doc.toString(indent);
	return base::to_string(qstr);
}
