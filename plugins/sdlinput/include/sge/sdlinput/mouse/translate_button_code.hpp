//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SDLINPUT_MOUSE_TRANSLATE_BUTTON_CODE_HPP_INCLUDED
#define SGE_SDLINPUT_MOUSE_TRANSLATE_BUTTON_CODE_HPP_INCLUDED

#include <sge/input/mouse/button_code.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::sdlinput::mouse
{

sge::input::mouse::button_code translate_button_code(std::uint8_t);

}

#endif
