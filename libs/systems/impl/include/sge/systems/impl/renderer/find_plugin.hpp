//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_IMPL_RENDERER_FIND_PLUGIN_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_RENDERER_FIND_PLUGIN_HPP_INCLUDED

#include <sge/renderer/caps/system_field_fwd.hpp>
#include <sge/renderer/plugin/collection_fwd.hpp>
#include <sge/systems/optional_name_fwd.hpp>
#include <sge/systems/renderer_caps_fwd.hpp>
#include <sge/systems/impl/renderer/plugin_core_pair_fwd.hpp>
#include <fcppt/log/context_reference_fwd.hpp>


namespace sge::systems::impl::renderer
{

sge::systems::impl::renderer::plugin_core_pair
find_plugin(
	fcppt::log::context_reference,
	sge::renderer::plugin::collection const &,
	sge::systems::optional_name const &,
	sge::renderer::caps::system_field const &,
	sge::systems::renderer_caps
);

}

#endif
