#pragma once
#include "qdom.h"
#include "QDomDocument"
#include <string>

namespace widget::xml
{
	class XmlSerializable
	{
	public:
		virtual ~XmlSerializable() = default;

		virtual QDomElement ToXml(QDomDocument &doc) const = 0;

		std::string ToXmlString(int indent) const;

		std::string ToXmlString() const
		{
			return ToXmlString(4);
		}
	};

} // namespace widget::xml
