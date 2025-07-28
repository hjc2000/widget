#pragma once
#include "qnamespace.h"
#include <cstdint>
#include <initializer_list>

namespace widget
{
	class AlignmentFlag
	{
	private:
		uint32_t _value = 0;

	public:
		AlignmentFlag(std::initializer_list<Qt::AlignmentFlag> const &list)
		{
			for (Qt::AlignmentFlag const &flag : list)
			{
				_value |= static_cast<uint32_t>(flag);
			}
		}

		operator Qt::AlignmentFlag() const
		{
			return static_cast<Qt::AlignmentFlag>(_value);
		}
	};

} // namespace widget
