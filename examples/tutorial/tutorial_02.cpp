/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/external_system_impl.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/sprite/no_color.hpp>
#include <sge/sprite/choices.hpp>
#include <sge/sprite/type_choices.hpp>
#include <sge/sprite/with_texture.hpp>
#include <sge/sprite/render_one.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/input/key_type.hpp>
#include <sge/input/key_pair.hpp>
#include <sge/input/system.hpp>
#include <sge/image/file.hpp>
#include <sge/image/file_ptr.hpp>
#include <sge/image/colors.hpp>
#include <sge/image/multi_loader.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/mainloop/dispatch.hpp>
#include <sge/window/parameters.hpp>
#include <sge/config/media_path.hpp>
#include <sge/exception.hpp>
#include <sge/extension_set.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/text.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <exception>
#include <iostream>
#include <ostream>
#include <cstdlib>

namespace
{

typedef sge::sprite::choices<
	sge::sprite::type_choices<
		int,
		float,
		sge::sprite::no_color
	>,
	boost::mpl::vector1<
		sge::sprite::with_texture
	>
> sprite_choices;

typedef sge::sprite::object<
	sprite_choices
> sprite_object;

class input_functor
{
public:
	explicit input_functor(
		bool &running
	)
	:
		running(running)
	{}

	void
	operator()(
		sge::input::key_pair const &k
	) const
	{
		if(
			k.key().code() == sge::input::kc::key_escape
		)
			running = false;
	}
private:
	bool &running;
};

class sprite_functor
{
public:
	explicit sprite_functor(
		sprite_object &s
	)
	:
		s(s)
	{}

	void
	operator()(
		sge::input::key_pair const &k
	) const
	{
		switch(
			k.key().code()
		)
		{
		case sge::input::kc::mouse_x_axis:
			s.x(
				s.x() + k.value()
			);
			break;
		case sge::input::kc::mouse_y_axis:
			s.y(
				s.y() + k.value()
			);
			break;
		default:
			break;
		}
	}
private:
	sprite_object &s;
};
}

int main()
try
{
	sge::systems::instance const sys(
		sge::systems::list()
		(
			sge::window::parameters(
				FCPPT_TEXT("sge tutorial02")
			)
		)
		(
			sge::renderer::parameters(
				sge::renderer::display_mode(
					sge::renderer::screen_size(
						640,
						480
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
			sge::systems::image_loader(
				sge::image::capabilities_field::null(),
				fcppt::assign::make_container<
					sge::extension_set
				>(
					FCPPT_TEXT("png")
				)
			)
		)
		(
			sge::systems::parameterless::input
		)
	);

	typedef sge::sprite::system<
		sprite_choices
	>::type sprite_system;

	sprite_system ss(
		sys.renderer()
	);

	sge::image::file_ptr const image(
		sys.image_loader().load(
			sge::config::media_path()
			/ FCPPT_TEXT("tux.png")
		)
	);

	sge::renderer::texture_ptr const image_texture(
		sys.renderer()->create_texture(
			image->view(),
			sge::renderer::filter::linear,
			sge::renderer::resource_flags::readable
		)
	);

	typedef sge::sprite::parameters<
		sprite_choices
	> sprite_parameters;

	sprite_object my_object(
		sprite_parameters()
		.pos(
			sprite_object::point::null()
		)
		.texture(
			fcppt::make_shared_ptr<
				sge::texture::part_raw
			>(
				image_texture
			)
		)
		.texture_size()
		.elements()
	);

	bool running = true;

	fcppt::signal::scoped_connection const conn(
		sys.input_system()->register_callback(
			input_functor(
				running
			)
		)
	);

	fcppt::signal::scoped_connection const conn_other(
		sys.input_system()->register_callback(
			sprite_functor(
				my_object
			)
		)
	);

	sys.renderer()->state(
		sge::renderer::state::list
		(
			sge::renderer::state::bool_::clear_backbuffer = true
		)
		(
			sge::renderer::state::color::clear_color
				= sge::image::colors::black()
		)
	);

	while (running)
	{
		sge::mainloop::dispatch();

		sge::renderer::scoped_block const block_(
			sys.renderer()
		);

		sge::sprite::render_one(
			ss,
			my_object
		);
	}
}
catch (sge::exception const &e)
{
	fcppt::io::cerr
		<< FCPPT_TEXT("caught sge exception: ")
		<< e.string()
		<< FCPPT_TEXT('\n');

	return EXIT_FAILURE;
}
catch (std::exception const &e)
{
	std::cerr
		<< "caught std exception: "
		<< e.what()
		<< '\n';

	return EXIT_FAILURE;
}
