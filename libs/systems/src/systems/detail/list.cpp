//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/systems/detail/any.hpp>
#include <sge/systems/detail/any_list.hpp>
#include <sge/systems/detail/any_map.hpp>
#include <sge/systems/detail/list.hpp>
#include <sge/systems/impl/make_any_key.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::systems::detail::list::list(sge::systems::detail::any_list const &_elements)
    : states_(fcppt::algorithm::map<sge::systems::detail::any_map>(
          _elements,
          [](sge::systems::detail::any const &_any)
          { return std::make_pair(sge::systems::impl::make_any_key(_any), _any); }))
{
  FCPPT_ASSERT_ERROR(_elements.size() == states_.size());
}

sge::systems::detail::any_map const &sge::systems::detail::list::get() const { return states_; }
