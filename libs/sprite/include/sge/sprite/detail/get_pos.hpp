//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_DETAIL_GET_POS_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_GET_POS_HPP_INCLUDED

#include <sge/sprite/config/pos_option.hpp>
#include <sge/sprite/detail/pos_from_center.hpp>
#include <sge/sprite/roles/center.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/pos_or_center.hpp>
#include <sge/sprite/types/center.hpp>
#include <sge/sprite/types/pos.hpp>
#include <sge/sprite/types/vector.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::sprite::detail
{

template <typename Choices, typename Elements>
inline typename std::enable_if<
    Choices::pos_choice::option::value == sge::sprite::config::pos_option::pos,
    sge::sprite::types::vector<typename Choices::type_choices>>::type
get_pos(Elements const &_elements)
{
  return fcppt::record::get<sge::sprite::roles::pos>(_elements);
}

template <typename Choices, typename Elements>
inline typename std::enable_if<
    Choices::pos_choice::option::value == sge::sprite::config::pos_option::center,
    sge::sprite::types::vector<typename Choices::type_choices>>::type
get_pos(Elements const &_elements)
{
  return sge::sprite::detail::pos_from_center<Choices>(
      _elements,
      sge::sprite::types::center<typename Choices::type_choices>{
          fcppt::record::get<sge::sprite::roles::center>(_elements)});
}

template <typename Choices, typename Elements>
inline typename std::enable_if<
    Choices::pos_choice::option::value == sge::sprite::config::pos_option::pos_or_center,
    sge::sprite::types::vector<typename Choices::type_choices>>::type
get_pos(Elements const &_elements)
{
  return fcppt::variant::match(
      fcppt::record::get<sge::sprite::roles::pos_or_center>(_elements),
      [](sge::sprite::types::pos<typename Choices::type_choices> const _pos) { return _pos.get(); },
      [&_elements](sge::sprite::types::center<typename Choices::type_choices> const _center)
      { return sge::sprite::detail::pos_from_center<Choices>(_elements, _center); });
}

}

#endif
