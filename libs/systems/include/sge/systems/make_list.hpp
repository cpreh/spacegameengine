//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SYSTEMS_MAKE_LIST_HPP_INCLUDED
#define SGE_SYSTEMS_MAKE_LIST_HPP_INCLUDED

#include <sge/systems/list.hpp>
#include <fcppt/tuple/make.hpp>
#include <fcppt/tuple/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::systems
{

template <typename Param>
[[nodiscard]] inline sge::systems::list<fcppt::tuple::object<std::remove_cvref_t<Param>>>
make_list(Param &&_param)
{
  return sge::systems::list<fcppt::tuple::object<std::remove_cvref_t<Param>>>{
      fcppt::tuple::make(std::forward<Param>(_param))};
}

}

#endif
