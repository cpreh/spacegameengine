/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/plugin/context.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/object.hpp>
#include <sge/renderer/bit_depth.hpp>
#include <sge/renderer/depth_stencil_buffer.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/plugin.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/system_scoped_ptr.hpp>
#include <sge/renderer/vsync.hpp>
#include <sge/renderer/windowed.hpp>
#include <sge/renderer/caps/object_output.hpp>
#include <sge/window/create_from_awl.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/title.hpp>
#include <awl/system/create.hpp>
#include <awl/system/object.hpp>
#include <awl/system/object_scoped_ptr.hpp>
#include <awl/visual/object.hpp>
#include <awl/visual/object_scoped_ptr.hpp>
#include <awl/window/object.hpp>
#include <awl/window/object_scoped_ptr.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdlib>
#include <fcppt/config/external_end.hpp>


int
main()
try
{
	sge::plugin::manager manager(
		sge::config::plugin_path()
	);

	typedef
	sge::plugin::object<
		sge::renderer::system
	>::ptr_type plugin_ptr;

	plugin_ptr const plugin(
		manager.plugin<
			sge::renderer::system
		>().load()
	);

	sge::renderer::system_scoped_ptr const render_sys(
		plugin->get()()
	);

	awl::system::object_scoped_ptr const window_sys(
		awl::system::create()
	);

	sge::renderer::parameters const render_params(
		sge::renderer::windowed(
			sge::renderer::bit_depth::depth32
		),
		sge::renderer::depth_stencil_buffer::off,
		sge::renderer::vsync::on,
		sge::renderer::no_multi_sampling
	);

	awl::visual::object_scoped_ptr const visual(
		render_sys->create_visual(
			*window_sys,
			render_params
		)
	);

	awl::window::object_scoped_ptr const window(
		sge::window::create_from_awl(
			*window_sys,
			*visual,
			sge::window::parameters(
				sge::window::title(
					FCPPT_TEXT("sge caps")
				),
				sge::window::dim(
					1024,
					768
				)
			)
		)
	);

	fcppt::io::cout()
		<<
		render_sys->create_renderer(
			render_params,
			sge::renderer::adapter(
				0u
			),
			*window
		)->caps()
		<< FCPPT_TEXT('\n');

	return EXIT_SUCCESS;
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return EXIT_FAILURE;
}
