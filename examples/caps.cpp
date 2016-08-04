/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/config/plugin_path.hpp>
#include <sge/log/default_level_streams.hpp>
#include <sge/plugin/collection.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/object.hpp>
#include <sge/plugin/optional_cache_ref.hpp>
#include <sge/renderer/core.hpp>
#include <sge/renderer/core_unique_ptr.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/system_unique_ptr.hpp>
#include <sge/renderer/caps/device_output.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/core_unique_ptr.hpp>
#include <sge/renderer/device/parameters.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/plugin/object.hpp>
#include <awl/system/create.hpp>
#include <awl/system/object.hpp>
#include <awl/system/object_unique_ptr.hpp>
#include <awl/system/event/processor.hpp>
#include <awl/visual/object.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <awl/window/object.hpp>
#include <awl/window/object_unique_ptr.hpp>
#include <awl/window/parameters.hpp>
#include <awl/window/event/processor.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/log/context.hpp>
#include <fcppt/log/enabled_levels.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/setting.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdlib>
#include <ostream>
#include <fcppt/config/external_end.hpp>


int
main()
try
{
	fcppt::log::context log_context{
		fcppt::log::setting{
			fcppt::log::enabled_levels(
				fcppt::log::level::debug
			)
		},
		sge::log::default_level_streams()
	};

	sge::plugin::manager manager(
		log_context,
		sge::config::plugin_path(),
		sge::plugin::optional_cache_ref()
	);

	sge::renderer::plugin::object const plugin(
		manager.collection<
			sge::renderer::core
		>().get(
			0u
		).load()
	);

	sge::renderer::core_unique_ptr const render_core(
		plugin.get()(
			log_context
		)
	);

	awl::system::object_unique_ptr const awl_system(
		awl::system::create(
			log_context
		)
	);

	sge::renderer::system_unique_ptr const render_sys(
		render_core->create_system(
			*awl_system
		)
	);

	awl::visual::object_unique_ptr const visual{
		render_sys->create_visual(
			sge::renderer::pixel_format::object{
				sge::renderer::pixel_format::color::depth32,
				sge::renderer::pixel_format::depth_stencil::off,
				sge::renderer::pixel_format::optional_multi_samples{},
				sge::renderer::pixel_format::srgb::no
			}
		)
	};

	awl::window::object_unique_ptr const window{
		awl_system->create_window(
			awl::window::parameters{
				*visual
			}
		)
	};

	sge::renderer::device::core_unique_ptr const render_device{
		render_sys->create_core_renderer(
			sge::renderer::device::parameters{
				sge::renderer::display_mode::parameters{
					sge::renderer::display_mode::vsync::on,
					sge::renderer::display_mode::optional_object{}
				},
				*window
			}
		)
	};

	fcppt::io::cout()
		<<
		std::boolalpha
		<<
		FCPPT_TEXT("Device ")
		<<
		FCPPT_TEXT(": ")
		<<
		render_device->caps()
		<<
		FCPPT_TEXT('\n');

	return
		EXIT_SUCCESS;
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return
		EXIT_FAILURE;
}
