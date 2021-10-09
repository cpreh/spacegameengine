//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SYSTEMS_DETAIL_HAS_WITH_WINDOW_HPP_INCLUDED
#define SGE_SYSTEMS_DETAIL_HAS_WITH_WINDOW_HPP_INCLUDED

#include <sge/systems/with_window_fwd.hpp>
#include <fcppt/mpl/list/contains.hpp>

namespace sge::systems::detail
{

template <typename Choices>
using has_with_window = fcppt::mpl::list::contains<Choices, sge::systems::with_window>;

}

#endif
