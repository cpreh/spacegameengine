//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_INPUT_KEY_MODIFIER_HPP_INCLUDED
#define SGE_INPUT_KEY_MODIFIER_HPP_INCLUDED

#include <sge/input/key/modifier_fwd.hpp> // IWYU pragma: keep

namespace sge::input::key
{

enum class modifier
{
  control,
  alt,
  shift,
  fcppt_maximum = shift
};

}

#endif
