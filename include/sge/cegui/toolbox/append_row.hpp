#ifndef SGE_CEGUI_TOOLBOX_APPEND_ROW_HPP_INCLUDED
#define SGE_CEGUI_TOOLBOX_APPEND_ROW_HPP_INCLUDED

#include <sge/cegui/toolbox/row.hpp>
#include <sge/cegui/symbol.hpp>
#include <CEGUI/elements/CEGUIMultiColumnList.h>

namespace sge
{
namespace cegui
{
namespace toolbox
{
SGE_CEGUI_SYMBOL void
append_row(
	CEGUI::MultiColumnList &,
	row const &);
}
}
}

#endif
