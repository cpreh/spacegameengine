//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CEGUI_IMPL_FROM_CEGUI_RECT_HPP_INCLUDED
#define SGE_CEGUI_IMPL_FROM_CEGUI_RECT_HPP_INCLUDED

#include <fcppt/math/box/rect.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Rect.h>
#include <fcppt/config/external_end.hpp>

namespace sge::cegui::impl
{

template <typename ValueType>
fcppt::math::box::rect<ValueType> from_cegui_rect(CEGUI::Rect<ValueType> const &_rect)
{
  using result_type = fcppt::math::box::rect<ValueType>;

  return result_type{
      typename result_type::vector{_rect.left(), _rect.top()},
      typename result_type::dim{_rect.getWidth(), _rect.getHeight()}};
}

}

#endif
