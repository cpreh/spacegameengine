//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CONSOLE_SIGNAL_FWD_HPP_INCLUDED
#define SGE_CONSOLE_SIGNAL_FWD_HPP_INCLUDED

#include <sge/console/callback/function_type.hpp>
#include <fcppt/signal/object_fwd.hpp>
#include <fcppt/signal/unregister/base_fwd.hpp>

namespace sge::console
{

using signal =
    fcppt::signal::object<sge::console::callback::function_type, fcppt::signal::unregister::base>;

}

#endif
