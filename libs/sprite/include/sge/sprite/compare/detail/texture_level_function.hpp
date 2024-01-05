//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_COMPARE_DETAIL_TEXTURE_LEVEL_FUNCTION_HPP_INCLUDED
#define SGE_SPRITE_COMPARE_DETAIL_TEXTURE_LEVEL_FUNCTION_HPP_INCLUDED

#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/sprite/deref_texture.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/texture/part.hpp> // IWYU pragma: keep
#include <fcppt/make_cref.hpp>
#include <fcppt/reference_comparison.hpp> // IWYU pragma: keep
#include <fcppt/reference_impl.hpp>

namespace sge::sprite::compare::detail
{

template <template <typename> class Function, typename Level>
struct texture_level_function
{
  template <typename Choices>
  static bool
  execute(sge::sprite::object<Choices> const &_left, sge::sprite::object<Choices> const &_right)
  {
    return Function<fcppt::reference<sge::renderer::texture::planar const>>()(
        fcppt::make_cref(
            sge::sprite::deref_texture(_left.template texture_level<Level::value>()).texture()),
        fcppt::make_cref(
            sge::sprite::deref_texture(_right.template texture_level<Level::value>()).texture()));
  }
};

}

#endif
