//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SYSTEMS_DETAIL_QUIT_ON_ESCAPE_HPP_INCLUDED
#define SGE_SYSTEMS_DETAIL_QUIT_ON_ESCAPE_HPP_INCLUDED

#include <sge/systems/detail/symbol.hpp>
#include <sge/window/system_fwd.hpp>
#include <awl/event/base_fwd.hpp>

namespace sge::systems::detail
{

SGE_SYSTEMS_DETAIL_SYMBOL
void quit_on_escape(
    sge::window::system &, // NOLINT(google-runtime-references)
    awl::event::base const &);

}

#endif
