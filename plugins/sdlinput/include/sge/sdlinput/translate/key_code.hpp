//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SDLINPUT_TRANSLATE_KEY_CODE_HPP_INCLUDED
#define SGE_SDLINPUT_TRANSLATE_KEY_CODE_HPP_INCLUDED

#include <sge/input/key/code.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_keycode.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sdlinput
{
namespace translate
{

sge::input::key::code
key_code(
	SDL_Keycode
);

}
}
}

#endif
