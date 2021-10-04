//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GUI_STYLE_CREATE_HPP_INCLUDED
#define SGE_GUI_STYLE_CREATE_HPP_INCLUDED

#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/style/base_unique_ptr.hpp>


namespace sge::gui::style
{

SGE_GUI_DETAIL_SYMBOL
sge::gui::style::base_unique_ptr
create();

}

#endif
