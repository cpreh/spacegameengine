/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/renderer/caps.hpp>
#include <sge/renderer/create_device_with_window.hpp>
#include <sge/renderer/depth_buffer.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/display_mode.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/plugin.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/stencil_buffer.hpp>
#include <sge/renderer/system_ptr.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/vsync.hpp>
#include <sge/renderer/window_mode.hpp>
#include <sge/renderer/window_parameters.hpp>
#include <awl/system/create.hpp>
#include <awl/system/object_ptr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/text.hpp>

int main()
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

	sge::renderer::system_ptr const render_sys(
		plugin->get()()
	);

	awl::system::object_ptr const window_sys(
		awl::system::create()
	);

	fcppt::io::cout
		<<
		sge::renderer::create_device_with_window(
			window_sys,
			render_sys,
			sge::renderer::parameters(
				sge::renderer::display_mode(
					sge::renderer::screen_size(
						1024,
						768
					),
					sge::renderer::bit_depth::depth32,
					sge::renderer::refresh_rate_dont_care
				),
				sge::renderer::depth_buffer::off,
				sge::renderer::stencil_buffer::off,
				sge::renderer::window_mode::windowed,
				sge::renderer::vsync::on,
				sge::renderer::no_multi_sampling
			),
			static_cast<
				sge::renderer::adapter_type
			>(
				0
			),
			sge::renderer::window_parameters(
				FCPPT_TEXT("sge caps")
			)
		)->caps()
		<< FCPPT_TEXT('\n');
}
