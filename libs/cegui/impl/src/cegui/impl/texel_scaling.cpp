//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/cegui/impl/texel_scaling.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Size.h>
#include <CEGUI/Vector.h>
#include <fcppt/config/external_end.hpp>

CEGUI::Vector2f sge::cegui::impl::texel_scaling(CEGUI::Sizef const &_size)
{
  return CEGUI::Vector2f(
      fcppt::literal<CEGUI::Vector2f::value_type>(1) / _size.d_width,
      fcppt::literal<CEGUI::Vector2f::value_type>(1) / _size.d_height);
}
