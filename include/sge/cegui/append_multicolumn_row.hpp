#ifndef SGE_CEGUI_APPEND_MULTICOLUMN_ROW_HPP_INCLUDED
#define SGE_CEGUI_APPEND_MULTICOLUMN_ROW_HPP_INCLUDED

#include <sge/cegui/column_sequence.hpp>
#include <sge/cegui/symbol.hpp>
#include <CEGUI/elements/CEGUIMultiColumnList.h>

namespace sge
{
namespace cegui
{
SGE_CEGUI_SYMBOL void
append_multicolumn_row(
	CEGUI::MultiColumnList &,
	column_sequence const &);
}
}

#endif
