//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CEGUI_IMPL_CONVERT_CURSOR_BUTTON_HPP_INCLUDED
#define SGE_CEGUI_IMPL_CONVERT_CURSOR_BUTTON_HPP_INCLUDED

#include <sge/cegui/impl/optional_mouse_button_fwd.hpp>
#include <sge/input/cursor/button_code_fwd.hpp>


namespace sge::cegui::impl
{

sge::cegui::impl::optional_mouse_button
convert_cursor_button(
	sge::input::cursor::button_code
);

}

#endif
