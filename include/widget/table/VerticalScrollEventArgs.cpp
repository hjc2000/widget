#include "VerticalScrollEventArgs.h" // IWYU pragma: keep
#include "widget/table/Table.h"

int widget::VerticalScrollEventArgs::FirstVisibleRowIndex() const
{
	return _table->FirstVisibleRowIndex();
}
