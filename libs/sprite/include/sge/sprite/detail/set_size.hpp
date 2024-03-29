//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_DETAIL_SET_SIZE_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_SET_SIZE_HPP_INCLUDED

#include <sge/sprite/config/texture_size_option.hpp>
#include <sge/sprite/roles/size.hpp>
#include <sge/sprite/roles/size_or_texture_size.hpp>
#include <sge/sprite/types/dim.hpp>
#include <sge/sprite/types/size_or_texture_size.hpp>
#include <fcppt/record/set.hpp>

namespace sge::sprite::detail
{

template <typename Choices, typename Elements>
inline void
set_size(Elements &_elements, sge::sprite::types::dim<typename Choices::type_choices> const _size)
  requires(
      Choices::size_choice::texture_option::value ==
      sge::sprite::config::texture_size_option::never)
{
  fcppt::record::set<sge::sprite::roles::size>(_elements, _size);
}

template <typename Choices, typename Elements>
inline void
set_size(Elements &_elements, sge::sprite::types::dim<typename Choices::type_choices> const _size)
  requires(
      Choices::size_choice::texture_option::value ==
      sge::sprite::config::texture_size_option::maybe)
{
  fcppt::record::set<sge::sprite::roles::size_or_texture_size>(
      _elements, sge::sprite::types::size_or_texture_size<typename Choices::type_choices>(_size));
}
}

#endif
