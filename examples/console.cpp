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


#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/image_loader.hpp>
#include <sge/systems/running_to_false.hpp>
#include <sge/viewport/center_on_resize.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/texture/filter/linear.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/device.hpp>
#include <sge/texture/manager.hpp>
#include <sge/texture/add_image.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/image/colors.hpp>
#include <sge/image2d/multi_loader.hpp>
#include <sge/window/instance.hpp>
#include <sge/console/object.hpp>
#include <sge/console/arg_list.hpp>
#include <sge/console/gfx.hpp>
#include <sge/console/sprite_parameters.hpp>
#include <sge/console/sprite_object.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/font/text/lit.hpp>
#include <sge/font/text/to_fcppt_string.hpp>
#include <sge/font/metrics_ptr.hpp>
#include <sge/font/system.hpp>
#include <sge/config/media_path.hpp>
#include <sge/exception.hpp>
#include <sge/extension_set.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <boost/spirit/home/phoenix/object/construct.hpp>
#include <boost/spirit/home/phoenix/object/new.hpp>
#include <ostream>
#include <cstdlib>

namespace
{

void
fallback(
	sge::font::text::string const &_arg
)
{
	fcppt::io::cout
		<< FCPPT_TEXT("fallback called with argument:")
		<< sge::font::text::to_fcppt_string(
			_arg
		)
		<< FCPPT_TEXT('\n');
}

void
quit(
	bool &_running,
	sge::console::arg_list const &
)
{
	_running = false;
}

}

int main()
try
{
	bool running = true;

	sge::window::dim const window_dim(
		1024,
		768
	);

	sge::systems::instance const sys(
		sge::systems::list()
		(
			sge::systems::window(
				sge::window::simple_parameters(
					FCPPT_TEXT("sge console test"),
					window_dim
				)
			)
		)
		(
			sge::systems::renderer(
				sge::renderer::parameters(
					sge::renderer::visual_depth::depth32,
					sge::renderer::depth_stencil_buffer::off,
					sge::renderer::vsync::on,
					sge::renderer::no_multi_sampling
				),
				sge::viewport::center_on_resize(
					window_dim
				)
			)
		)
		(
			sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector
				),
				sge::systems::cursor_option_field::null()
			)
		)
		(
			sge::systems::parameterless::font
		)
		(
			sge::systems::image_loader(
				sge::image::capabilities_field::null(),
				fcppt::assign::make_container<
					sge::extension_set
				>(
					FCPPT_TEXT("png")
				)
			)
		)
	);

	fcppt::signal::scoped_connection const cb(
		sys.keyboard_collector().key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				sge::systems::running_to_false(
					running
				)
			)
		)
	);


	sge::console::object object(
		SGE_FONT_TEXT_LIT('/')
	);

	fcppt::signal::scoped_connection const c0(
		object.insert(
			SGE_FONT_TEXT_LIT("quit"),
			std::tr1::bind(
				&quit,
				fcppt::ref(
					running
				),
				std::tr1::placeholders::_1
			),
			SGE_FONT_TEXT_LIT("quit test")
		)
	);

	fcppt::signal::scoped_connection const c1(
		object.register_fallback(
			&fallback
		)
	);

	sge::texture::manager tex_man(
		boost::phoenix::construct<
			sge::texture::fragmented_unique_ptr
		>
		(
			boost::phoenix::new_<
				sge::texture::no_fragmented
			>
			(
				fcppt::ref(
					sys.renderer()
				),
				sge::image::color::format::rgba8,
				sge::renderer::texture::filter::linear,
				sge::renderer::texture::address_mode2(
					sge::renderer::texture::address_mode::repeat
				)
			)
		)
	);

	sge::texture::const_part_ptr const
		tex_bg(
			sge::texture::add_image(
				tex_man,
				*sys.image_loader().load(
					sge::config::media_path()
					/ FCPPT_TEXT("grass.png")
				)
			)
		);

	sge::font::metrics_ptr const font_metrics(
		sys.font_system().create_font(
			sge::config::media_path()
			/ FCPPT_TEXT("fonts")
			/ FCPPT_TEXT("default.ttf"),
			15
		)
	);

	sge::console::gfx gfx_(
		object,
		sys.renderer(),
		sge::image::colors::white(),
		*font_metrics,
		sys.keyboard_collector(),
		sge::console::sprite_object(
			sge::console::sprite_parameters()
			.pos(
				sge::console::sprite_object::vector::null()
			)
			.texture(
				tex_bg
			)
			.size(
				sge::console::sprite_object::dim(400,300)
			)
			.elements()
		),
		static_cast<
			sge::console::output_line_limit
		>(
			100
		)
	);

	sys.renderer().state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(sge::renderer::state::color::clear_color = sge::image::colors::black())
	);

	gfx_.active(true);

	while (running)
	{
		sys.window().dispatch();

		sge::renderer::scoped_block const block_(
			sys.renderer()
		);

		gfx_.draw();
	}
}
catch(sge::exception const &e)
{
	fcppt::io::cerr << e.string() << FCPPT_TEXT('\n');
	return EXIT_FAILURE;
}
catch(std::exception const &e)
{
	fcppt::io::cerr << e.what() << FCPPT_TEXT('\n');
	return EXIT_FAILURE;
}
