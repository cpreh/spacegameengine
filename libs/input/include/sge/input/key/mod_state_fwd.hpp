//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_KEY_MOD_STATE_FWD_HPP_INCLUDED
#define SGE_INPUT_KEY_MOD_STATE_FWD_HPP_INCLUDED

#include <sge/input/key/modifier.hpp>
#include <fcppt/container/bitfield/object_fwd.hpp>


namespace sge::input::key
{

using
mod_state
=
fcppt::container::bitfield::object<
	sge::input::key::modifier
>;

}

#endif
