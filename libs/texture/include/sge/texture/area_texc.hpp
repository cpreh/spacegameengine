//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_TEXTURE_AREA_TEXC_HPP_INCLUDED
#define SGE_TEXTURE_AREA_TEXC_HPP_INCLUDED

#include <sge/renderer/is_valid_float_type.hpp>
#include <sge/texture/part_fwd.hpp>
#include <sge/texture/detail/symbol.hpp>
#include <fcppt/math/box/rect.hpp>
#include <fcppt/math/vector/static_fwd.hpp>

namespace sge::texture
{

template <typename T>
SGE_TEXTURE_DETAIL_SYMBOL fcppt::math::box::rect<T>
area_texc(sge::texture::part const &, fcppt::math::vector::static_<T, 2> const &repeat)
  requires(sge::renderer::is_valid_float_type<T>::value);
}

#define SGE_TEXTURE_DETAIL_DECLARE_AREA_TEXC(floattype) \
  extern template SGE_TEXTURE_DETAIL_SYMBOL \
  fcppt::math::box::rect<floattype> \
  sge::texture::area_texc<floattype>( \
      sge::texture::part const &, fcppt::math::vector::static_<floattype, 2> const &) \
  requires(sge::renderer::is_valid_float_type<floattype>::value)

SGE_TEXTURE_DETAIL_DECLARE_AREA_TEXC(float);

SGE_TEXTURE_DETAIL_DECLARE_AREA_TEXC(double);

#endif
