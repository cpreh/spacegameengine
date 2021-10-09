//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/screen_size.hpp>
#include <sge/viewport/aspect_from_screen_size.hpp>
#include <sge/viewport/fractional_aspect.hpp>
#include <fcppt/cast/size.hpp>

sge::viewport::fractional_aspect
sge::viewport::aspect_from_screen_size(sge::renderer::screen_size const &_screen_size)
{
  return sge::viewport::fractional_aspect{
      fcppt::cast::size<sge::viewport::fractional_aspect::value_type>(_screen_size.w()),
      fcppt::cast::size<sge::viewport::fractional_aspect::value_type>(_screen_size.h())};
}
