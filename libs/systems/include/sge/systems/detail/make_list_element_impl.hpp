//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SYSTEMS_DETAIL_MAKE_LIST_ELEMENT_IMPL_HPP_INCLUDED
#define SGE_SYSTEMS_DETAIL_MAKE_LIST_ELEMENT_IMPL_HPP_INCLUDED

#include <sge/systems/renderer.hpp>
#include <sge/systems/detail/any.hpp>
#include <sge/systems/detail/renderer.hpp>
#include <sge/systems/detail/renderer_caps.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace sge::systems::detail
{

template <typename Choices, typename Type>
inline sge::systems::detail::any make_list_element_impl(Type &&_value)
  requires(std::negation_v<std::is_same<std::remove_cvref_t<Type>, sge::systems::renderer>>)
{
  return sge::systems::detail::any{std::forward<Type>(_value)};
}

template <typename Choices, typename Type>
inline sge::systems::detail::any make_list_element_impl(Type &&_value)
  requires(std::is_same_v<std::remove_cvref_t<Type>, sge::systems::renderer>)
{
  return sge::systems::detail::any{sge::systems::detail::renderer{
      std::forward<Type>(_value), sge::systems::detail::renderer_caps<Choices>::value}};
}

}

#endif
