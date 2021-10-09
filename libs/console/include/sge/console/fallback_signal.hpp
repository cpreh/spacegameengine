//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CONSOLE_FALLBACK_SIGNAL_HPP_INCLUDED
#define SGE_CONSOLE_FALLBACK_SIGNAL_HPP_INCLUDED

#include <sge/console/fallback_function.hpp>
#include <fcppt/signal/object_fwd.hpp>

namespace sge::console
{

using fallback_signal = fcppt::signal::object<sge::console::fallback_function>;

}

#endif
