//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_DETAIL_SIZE_FROM_TEXTURE_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_SIZE_FROM_TEXTURE_HPP_INCLUDED

#include <sge/sprite/deref_texture.hpp>
#include <sge/sprite/texture.hpp>
#include <sge/sprite/roles/texture0.hpp>
#include <sge/sprite/types/dim.hpp>
#include <sge/texture/part.hpp>
#include <fcppt/cast/static_cast_fun.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/record/get.hpp>

namespace sge::sprite::detail
{

template <typename Choices, typename Elements>
inline sge::sprite::types::dim<typename Choices::type_choices>
size_from_texture(Elements const &_elements)
{
  return fcppt::math::dim::structure_cast<
      sge::sprite::types::dim<typename Choices::type_choices>,
      fcppt::cast::static_cast_fun>(
      sge::sprite::deref_texture(fcppt::record::get<sge::sprite::roles::texture0>(_elements))
          .size());
}

}

#endif
