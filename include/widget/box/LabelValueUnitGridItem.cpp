#include "LabelValueUnitGridItem.h"
#include "base/string/define.h"
#include <stdexcept>

widget::LabelValueUnitGridItem::LabelValueUnitGridItem(int row,
													   int column,
													   std::shared_ptr<QWidget> label,
													   std::shared_ptr<QWidget> data,
													   std::shared_ptr<QWidget> unit)
{
	if (label == nullptr)
	{
		throw std::invalid_argument{CODE_POS_STR + "禁止传入空指针。"};
	}

	if (data == nullptr)
	{
		throw std::invalid_argument{CODE_POS_STR + "禁止传入空指针。"};
	}

	if (unit == nullptr)
	{
		throw std::invalid_argument{CODE_POS_STR + "禁止传入空指针。"};
	}

	_label = label;
	_data = data;
	_unit = unit;
}
