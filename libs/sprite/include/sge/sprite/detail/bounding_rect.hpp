//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_DETAIL_BOUNDING_RECT_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_BOUNDING_RECT_HPP_INCLUDED

#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/types/rect.hpp>

namespace sge::sprite::detail
{

template <typename Choices>
sge::sprite::types::rect<typename Choices::type_choices>
bounding_rect(sge::sprite::object<Choices> const &_sprite)
{
  return sge::sprite::types::rect<typename Choices::type_choices>(_sprite.pos(), _sprite.size());
}

}

#endif
