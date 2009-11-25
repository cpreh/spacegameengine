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
#include <sge/config/media_path.hpp>
#include <sge/signal/scoped_connection.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <sge/input/system.hpp>
#include <sge/input/action.hpp>
#include <sge/image/loader.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/sprite/texture_animation.hpp>
#include <sge/texture/manager.hpp>
#include <sge/texture/add_image.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/texture/default_creator.hpp>
#include <sge/texture/default_creator_impl.hpp>
#include <sge/time/millisecond.hpp>
#include <sge/time/second.hpp>
#include <sge/time/resolution.hpp>
#include <sge/mainloop/dispatch.hpp>
#include <sge/assign/make_container.hpp>
#include <sge/log/global.hpp>
#include <sge/log/activate_levels.hpp>
#include <sge/cerr.hpp>
#include <sge/exception.hpp>
#include <boost/spirit/home/phoenix/core/reference.hpp>
#include <boost/spirit/home/phoenix/operator/self.hpp>
#include <cstdlib>
#include <exception>
#include <ostream>

int main()
try
{
	sge::log::activate_levels(
		sge::log::global(),
		sge::log::level::debug
	);

	sge::systems::instance const sys(
		sge::systems::list()
		(
			sge::window::parameters(
				SGE_TEXT("sge animtest")
			)
		)
		(
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
			)
		)
		(
			sge::systems::parameterless::input
		)
		(
			sge::systems::parameterless::image
		)
	);

	sge::input::system_ptr const    is   = sys.input_system();
	sge::renderer::device_ptr const rend = sys.renderer();
	sge::image::loader_ptr const    pl   = sys.image_loader();


	sge::texture::default_creator<
		sge::texture::no_fragmented
	> const creator(
		rend,
		sge::image::color::format::rgba8,
		sge::renderer::filter::linear
	);

	sge::texture::manager tex_man(rend, creator);

	sge::texture::const_part_ptr const
		tex1(
			sge::texture::add_image(
				tex_man,
				pl->load(
					sge::config::media_path() / SGE_TEXT("cloudsquare.jpg")
				)
			)
		),
		tex2(
			sge::texture::add_image(
				tex_man,
				pl->load(
					sge::config::media_path() / SGE_TEXT("grass.png")
				)
			)
		);

	sge::sprite::system ss(rend);
	sge::sprite::object spr(
		sge::sprite::parameters()
		.size(
			sge::sprite::dim(
				rend->screen_size().w(),
				static_cast<sge::sprite::unit>(
					rend->screen_size().h()
				)
			)
		)
	);

	sge::sprite::animation_series::entity_vector const series(
		sge::assign::make_container<
			sge::sprite::animation_series::entity_vector
		>(
			sge::sprite::animation_entity(
				sge::time::millisecond(500),
				tex1
			)
		)
		(
			sge::sprite::animation_entity(
				sge::time::second(
					1
				),
				tex2
			)
		)
	);

	sge::sprite::texture_animation anim(
		series,
		sge::sprite::texture_animation::loop_method::repeat,
		spr
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

	rend->state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_backbuffer = true)
	);

	while(running)
	{
		sge::mainloop::dispatch();
		sge::renderer::scoped_block const block_(rend);
		anim.process();
		ss.render(spr);
	}
}
catch(sge::exception const &e)
{
	sge::cerr << e.string() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}
catch(std::exception const &e)
{
	sge::cerr << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}
