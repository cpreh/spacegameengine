//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_WINDOW_SOURCE_FWD_HPP_INCLUDED
#define SGE_SYSTEMS_WINDOW_SOURCE_FWD_HPP_INCLUDED

#include <sge/systems/original_window_fwd.hpp>
#include <sge/systems/wrapped_window_fwd.hpp>
#include <fcppt/variant/variadic_fwd.hpp>


namespace sge
{
namespace systems
{

typedef
fcppt::variant::variadic<
	sge::systems::original_window,
	sge::systems::wrapped_window
>
window_source;

}
}

#endif
