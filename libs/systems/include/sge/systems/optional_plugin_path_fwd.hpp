//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_OPTIONAL_PLUGIN_PATH_FWD_HPP_INCLUDED
#define SGE_SYSTEMS_OPTIONAL_PLUGIN_PATH_FWD_HPP_INCLUDED

#include <sge/systems/plugin_path.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sge::systems
{

using
optional_plugin_path
=
fcppt::optional::object<
	sge::systems::plugin_path
>;

}

#endif
