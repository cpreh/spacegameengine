//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_KEYBOARD_KEY_ID_HPP_INCLUDED
#define SGE_INPUT_KEYBOARD_KEY_ID_HPP_INCLUDED

#include <sge/input/info/id.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sge::input::keyboard
{

FCPPT_DECLARE_STRONG_TYPEDEF(
	sge::input::info::id,
	key_id
);

}

#endif
