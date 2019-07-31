//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CEGUI_TOOLBOX_APPEND_ROW_HPP_INCLUDED
#define SGE_CEGUI_TOOLBOX_APPEND_ROW_HPP_INCLUDED

#include <sge/cegui/detail/symbol.hpp>
#include <sge/cegui/toolbox/row.hpp>


namespace CEGUI
{
class MultiColumnList;
}

namespace sge
{
namespace cegui
{
namespace toolbox
{

SGE_CEGUI_DETAIL_SYMBOL
void
append_row(
	CEGUI::MultiColumnList &,
	sge::cegui::toolbox::row const &
);

}
}
}

#endif
