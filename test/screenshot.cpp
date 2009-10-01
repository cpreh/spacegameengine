/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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



#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/mainloop/catch_block.hpp>
#include <sge/mainloop/dispatch.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/screenshot.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <sge/input/action.hpp>
#include <sge/input/system.hpp>
#include <sge/image/loader.hpp>
#include <sge/image/colors.hpp>
#include <sge/texture/manager.hpp>
#include <sge/texture/default_creator_impl.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/texture/part.hpp>
#include <sge/texture/add_image.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/sprite/object.hpp>
#include <sge/signal/scoped_connection.hpp>
#include <sge/window/parameters.hpp>
#include <sge/config/media_path.hpp>
#include <sge/text.hpp>
#include <boost/spirit/home/phoenix/core/reference.hpp>
#include <boost/spirit/home/phoenix/operator/self.hpp>
#include <tr1/functional>

int main()
try
{
	sge::systems::instance const sys(
		sge::systems::list()
		(sge::window::parameters(
			SGE_TEXT("sge animtest")
		))
		(sge::renderer::parameters(
			sge::renderer::display_mode(
				sge::renderer::screen_size(
					1024,
					768),
				sge::renderer::bit_depth::depth32,
				sge::renderer::refresh_rate_dont_care),
			sge::renderer::depth_buffer::off,
			sge::renderer::stencil_buffer::off,
			sge::renderer::window_mode::windowed))
		(sge::systems::parameterless::input)
		(sge::systems::parameterless::image)
	);

	sge::renderer::device_ptr const device(
		sys.renderer()
	);

	sge::input::system_ptr const is(
		sys.input_system()
	);

	sge::image::loader_ptr const loader(
		sys.image_loader()
	);

	sge::texture::manager tex_man(
		device,
		sge::texture::default_creator<
			sge::texture::no_fragmented
		>(
			device,
			sge::image::color::format::rgba8,
			sge::renderer::filter::linear
		)
	);

	sge::texture::const_part_ptr const tex(
		sge::texture::add_image(
			tex_man,
			sys.image_loader()->load(
				sge::config::media_path() / SGE_TEXT("tux.png")
			)
		)
	);

	sge::sprite::system ss(
		device
	);

	sge::sprite::object bg(
		sge::sprite::parameters()
			.texture(tex)
	);

	device->state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(sge::renderer::state::color::clear_color
				= sge::image::colors::green())
	);

	bool running = true;

	sge::signal::scoped_connection const cb(
		is->register_callback(
			sge::input::action(
				sge::input::kc::key_escape,
				boost::phoenix::ref(running) = false
			)
		)
	);

	sge::signal::scoped_connection const cb2(
		is->register_callback(
			sge::input::action(
				sge::input::kc::key_f12,
				std::tr1::bind(
					sge::renderer::screenshot,
					device,
					loader,
					sge::filesystem::path(
						SGE_TEXT("output.png")
					)
				)
			)
		)
	);
	
	while(running)
	{
		sge::mainloop::dispatch();

		sge::renderer::scoped_block const block_(
			device
		);

		ss.render(bg);
	}
}
SGE_MAINLOOP_CATCH_BLOCK
