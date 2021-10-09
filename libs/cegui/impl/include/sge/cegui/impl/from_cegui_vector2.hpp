//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CEGUI_IMPL_FROM_CEGUI_VECTOR2_HPP_INCLUDED
#define SGE_CEGUI_IMPL_FROM_CEGUI_VECTOR2_HPP_INCLUDED

#include <fcppt/math/vector/static.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Vector.h>
#include <fcppt/config/external_end.hpp>

namespace sge::cegui::impl
{

template <typename ValueType>
fcppt::math::vector::static_<ValueType, 2U>
from_cegui_vector2(CEGUI::Vector2<ValueType> const &_size)
{
  return fcppt::math::vector::static_<ValueType, 2U>{_size.d_x, _size.d_y};
}

}

#endif
