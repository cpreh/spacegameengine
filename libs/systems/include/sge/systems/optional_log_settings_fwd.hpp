//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_OPTIONAL_LOG_SETTINGS_FWD_HPP_INCLUDED
#define SGE_SYSTEMS_OPTIONAL_LOG_SETTINGS_FWD_HPP_INCLUDED

#include <sge/systems/log_settings_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sge::systems
{

using
optional_log_settings
=
fcppt::optional::object<
	sge::systems::log_settings
>;

}

#endif
