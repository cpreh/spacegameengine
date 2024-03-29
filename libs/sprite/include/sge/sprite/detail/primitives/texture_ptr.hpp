//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_DETAIL_PRIMITIVES_TEXTURE_PTR_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_PRIMITIVES_TEXTURE_PTR_HPP_INCLUDED

#include <sge/sprite/config/texture_ownership_fwd.hpp>
#include <sge/sprite/detail/transform_texture_levels_static.hpp>
#include <sge/sprite/detail/primitives/texture_ref_type.hpp>
#include <sge/sprite/roles/texture.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/record/element.hpp>

namespace sge::sprite::detail::primitives
{

template <typename Choices, typename Levels, sge::sprite::config::texture_ownership Ownership>
struct texture_ptr
{
private:
  template <typename Level>
  using make_role = fcppt::record::element<
      sge::sprite::roles::texture<Level::value>,
      typename sge::sprite::detail::primitives::texture_ref_type<Ownership>::type>;

public:
  using type =
      sge::sprite::detail::transform_texture_levels_static<fcppt::mpl::lambda<make_role>, Levels>;
};

}

#endif
