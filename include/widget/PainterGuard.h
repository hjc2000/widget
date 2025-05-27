#pragma once
#include "base/string/define.h"
#include "qpainter.h"
#include <stdexcept>

namespace widget
{
	class PainterGuard
	{
	private:
		QPainter *_painter = nullptr;

	public:
		PainterGuard(QPainter &painter)
			: _painter(&painter)
		{
			_painter->save();
		}

		PainterGuard(QPainter *painter)
		{
			if (painter == nullptr)
			{
				throw std::invalid_argument{CODE_POS_STR + "禁止传入空指针。"};
			}

			_painter = painter;
			_painter->save();
		}

		~PainterGuard()
		{
			_painter->restore();
		}
	};

} // namespace widget
