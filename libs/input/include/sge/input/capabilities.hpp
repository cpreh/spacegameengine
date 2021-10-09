//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_INPUT_CAPABILITIES_HPP_INCLUDED
#define SGE_INPUT_CAPABILITIES_HPP_INCLUDED

#include <sge/input/capabilities_fwd.hpp>

namespace sge::input
{

enum class capabilities
{
  cursor,
  focus,
  joypad,
  keyboard,
  mouse,
  fcppt_maximum = mouse
};

}

#endif
