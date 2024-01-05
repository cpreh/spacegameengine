//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SYSTEMS_LIST_IMPL_HPP_INCLUDED
#define SGE_SYSTEMS_LIST_IMPL_HPP_INCLUDED

#include <sge/systems/list_decl.hpp> // IWYU pragma: export
#include <fcppt/tuple/push_back.hpp>
#include <fcppt/tuple/push_back_result.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <utility>
#include <fcppt/config/external_end.hpp>

template <typename Inits>
sge::systems::list<Inits>::list(Inits &&_inits) : inits_{std::move(_inits)}
{
}

template <typename Inits>
template <typename Param>
sge::systems::list<fcppt::tuple::push_back_result<Inits, std::remove_cvref_t<Param>>>
sge::systems::list<Inits>::operator()(Param &&_param) const
{
  return sge::systems::list<fcppt::tuple::push_back_result<Inits, std::remove_cvref_t<Param>>>(
      fcppt::tuple::push_back(inits_, std::forward<Param>(_param)));
}

template <typename Inits>
Inits &sge::systems::list<Inits>::get()
{
  return inits_;
}

template <typename Inits>
Inits const &sge::systems::list<Inits>::get() const
{
  return inits_;
}

#endif
