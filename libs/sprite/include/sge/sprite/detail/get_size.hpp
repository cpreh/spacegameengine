//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_DETAIL_GET_SIZE_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_GET_SIZE_HPP_INCLUDED

#include <sge/sprite/config/texture_size_option.hpp>
#include <sge/sprite/detail/size_from_texture.hpp>
#include <sge/sprite/roles/size.hpp>
#include <sge/sprite/roles/size_or_texture_size.hpp>
#include <sge/sprite/types/dim.hpp>
#include <sge/sprite/types/texture_size.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::sprite::detail
{

template <typename Choices, typename Elements>
inline typename std::enable_if<
    Choices::size_choice::texture_option::value == sge::sprite::config::texture_size_option::always,
    sge::sprite::types::dim<typename Choices::type_choices>>::type
get_size(Elements const &_elements)
{
  return sge::sprite::detail::size_from_texture<Choices>(_elements);
}

template <typename Choices, typename Elements>
inline typename std::enable_if<
    Choices::size_choice::texture_option::value == sge::sprite::config::texture_size_option::never,
    sge::sprite::types::dim<typename Choices::type_choices>>::type
get_size(Elements const &_elements)
{
  return fcppt::record::get<sge::sprite::roles::size>(_elements);
}

template <typename Choices, typename Elements>
inline typename std::enable_if<
    Choices::size_choice::texture_option::value == sge::sprite::config::texture_size_option::maybe,
    sge::sprite::types::dim<typename Choices::type_choices>>::type
get_size(Elements const &_elements)
{
  return fcppt::variant::match(
      fcppt::record::get<sge::sprite::roles::size_or_texture_size>(_elements),
      [](sge::sprite::types::dim<typename Choices::type_choices> _dim) { return _dim; },
      [&_elements](sge::sprite::types::texture_size)
      { return sge::sprite::detail::size_from_texture<Choices>(_elements); });
}

}

#endif
