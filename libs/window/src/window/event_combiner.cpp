//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/window/event_combiner.hpp>
#include <awl/event/base.hpp>
#include <awl/event/container.hpp>
#include <fcppt/container/join.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

awl::event::container sge::window::event_combiner(
    awl::event::container &&_container1, awl::event::container &&_container2)
{
  return fcppt::container::join(std::move(_container1), std::move(_container2));
}
