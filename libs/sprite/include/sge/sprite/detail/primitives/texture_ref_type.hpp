//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_DETAIL_PRIMITIVES_TEXTURE_REF_TYPE_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_PRIMITIVES_TEXTURE_REF_TYPE_HPP_INCLUDED

#include <sge/sprite/config/texture_ownership.hpp>
#include <sge/texture/const_part_ref.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <sge/texture/const_part_unique_ptr.hpp>

namespace sge::sprite::detail::primitives
{

template <sge::sprite::config::texture_ownership Ownership>
struct texture_ref_type;

template <>
struct texture_ref_type<sge::sprite::config::texture_ownership::reference>
{
  using type = sge::texture::const_part_ref;
};

template <>
struct texture_ref_type<sge::sprite::config::texture_ownership::unique>
{
  using type = sge::texture::const_part_unique_ptr;
};

template <>
struct texture_ref_type<sge::sprite::config::texture_ownership::shared>
{
  using type = sge::texture::const_part_shared_ptr;
};

}

#endif
