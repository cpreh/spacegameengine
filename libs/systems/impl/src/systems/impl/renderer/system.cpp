//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/parse/ini/entry_name.hpp>
#include <sge/parse/ini/optional_start_fwd.hpp>
#include <sge/renderer/core.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/plugin/collection_fwd.hpp>
#include <sge/systems/detail/renderer.hpp>
#include <sge/systems/impl/merge_config_strings.hpp>
#include <sge/systems/impl/renderer/find_plugin.hpp>
#include <sge/systems/impl/renderer/system.hpp>
#include <sge/systems/impl/window/system.hpp>
#include <sge/window/system.hpp>
#include <awl/visual/object.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <fcppt/log/context_fwd.hpp>


sge::systems::impl::renderer::system::system(
	fcppt::log::context &_log_context,
	sge::renderer::plugin::collection const &_collection,
	sge::systems::detail::renderer const &_parameters,
	sge::parse::ini::optional_start const &_config,
	sge::systems::impl::window::system const &_window_system
)
:
	pixel_format_(
		_parameters.parameters().pixel_format()
	),
	plugin_core_pair_(
		sge::systems::impl::renderer::find_plugin(
			_log_context,
			_collection,
			sge::systems::impl::merge_config_strings(
				_parameters.parameters().name(),
				_config,
				sge::parse::ini::entry_name(
					"renderer"
				)
			),
			_parameters.parameters().caps(),
			_parameters.caps()
		)
	),
	renderer_system_(
		plugin_core_pair_.system().create_system(
			_window_system.get()
		)
	)
{
}

sge::systems::impl::renderer::system::~system()
{
}

awl::visual::object_unique_ptr
sge::systems::impl::renderer::system::create_visual()
{
	return
		this->get().create_visual(
			pixel_format_
		);
}

sge::renderer::core &
sge::systems::impl::renderer::system::core() const
{
	return
		plugin_core_pair_.system();
}

sge::renderer::system &
sge::systems::impl::renderer::system::get() const
{
	return
		*renderer_system_;
}
