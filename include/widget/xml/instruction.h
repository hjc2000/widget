#pragma once
#include "qdom.h"
#include "QDomDocument"

namespace widget::xml::instruction
{
	inline QDomProcessingInstruction Utf8EncodingDeclarationInstruction(QDomDocument &doc)
	{
		QDomProcessingInstruction encodingDeclaration = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"utf-8\"");
		return encodingDeclaration;
	}

} // namespace widget::xml::instruction
