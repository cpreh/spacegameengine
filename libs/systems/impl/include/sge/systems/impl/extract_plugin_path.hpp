//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_IMPL_EXTRACT_PLUGIN_PATH_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_EXTRACT_PLUGIN_PATH_HPP_INCLUDED

#include <sge/systems/plugin_path.hpp>
#include <sge/systems/detail/any_map.hpp>


namespace sge
{
namespace systems
{
namespace impl
{

sge::systems::plugin_path
extract_plugin_path(
	sge::systems::detail::any_map const &
);

}
}
}

#endif
