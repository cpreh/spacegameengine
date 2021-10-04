//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_MOUSE_BUTTON_CODE_TO_STRING_HPP_INCLUDED
#define SGE_INPUT_MOUSE_BUTTON_CODE_TO_STRING_HPP_INCLUDED

#include <sge/input/detail/symbol.hpp>
#include <sge/input/mouse/button_code_fwd.hpp>
#include <fcppt/string.hpp>


namespace sge::input::mouse
{

SGE_INPUT_DETAIL_SYMBOL
fcppt::string
button_code_to_string(
	sge::input::mouse::button_code
);

}

#endif
