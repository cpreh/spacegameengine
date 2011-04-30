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
#include <sge/viewport/center_on_resize.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/external_system_impl.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/sprite/no_color.hpp>
#include <sge/sprite/choices.hpp>
#include <sge/sprite/type_choices.hpp>
#include <sge/sprite/with_dim.hpp>
#include <sge/sprite/with_texture.hpp>
#include <sge/sprite/render_one.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/texture/filter/linear.hpp>
#include <sge/renderer/texture/address_mode2.hpp>
#include <sge/renderer/texture/create_planar_from_view.hpp>
#include <sge/renderer/texture/planar_ptr.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/mouse/axis_event.hpp>
#include <sge/input/mouse/device.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/file_ptr.hpp>
#include <sge/image2d/multi_loader.hpp>
#include <sge/image/colors.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/window/instance.hpp>
#include <sge/config/media_path.hpp>
#include <sge/exception.hpp>
#include <sge/extension_set.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/text.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/nonassignable.hpp>
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
	boost::mpl::vector2<
		sge::sprite::with_dim,
		sge::sprite::with_texture
	>
> sprite_choices;

typedef sge::sprite::object<
	sprite_choices
> sprite_object;

class input_functor
{
	FCPPT_NONASSIGNABLE(
		input_functor
	);
public:
	explicit input_functor(
		bool &_running
	)
	:
		running_(_running)
	{}

	void
	operator()(
		sge::input::keyboard::key_event const &k
	) const
	{
		if(
			k.pressed()
			&&
			k.key_code() == sge::input::keyboard::key_code::escape
		)
			running_ = false;
	}
private:
	bool &running_;
};

class sprite_functor
{
	FCPPT_NONASSIGNABLE(
		sprite_functor
	);
public:
	explicit sprite_functor(
		sprite_object &_sprite
	)
	:
		sprite_(_sprite)
	{}

	void
	operator()(
		sge::input::mouse::axis_event const &_event
	) const
	{
		switch(
			_event.axis()
		)
		{
		case sge::input::mouse::axis::x:
			sprite_.x(
				static_cast<
					sprite_object::unit
				>(
					sprite_.x() + _event.axis_value()
				)
			);
			break;
		case sge::input::mouse::axis::y:
			sprite_.y(
				static_cast<
					sprite_object::unit
				>(
					sprite_.y() + _event.axis_value()
				)
			);
			break;
		default:
			break;
		}
	}
private:
	sprite_object &sprite_;
};
}

int main()
try
{
	sge::window::dim const window_dim(
		640,
		480
	);

	sge::systems::instance const sys(
		sge::systems::list()
		(
			sge::systems::window(
				sge::window::simple_parameters(
					FCPPT_TEXT("sge tutorial02"),
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
			sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector
				)
				|
				sge::systems::input_helper::mouse_collector,
				sge::systems::cursor_option_field::null()
			)
		)
	);

	typedef sge::sprite::system<
		sprite_choices
	>::type sprite_system;

	sprite_system ss(
		sys.renderer()
	);

	sge::image2d::file_ptr const image(
		sys.image_loader().load(
			sge::config::media_path()
			/ FCPPT_TEXT("tux.png")
		)
	);

	sge::renderer::texture::planar_ptr const image_texture(
		sge::renderer::texture::create_planar_from_view(
			sys.renderer(),
			image->view(),
			sge::renderer::texture::filter::linear,
			sge::renderer::texture::address_mode2(
				sge::renderer::texture::address_mode::clamp
			),
			sge::renderer::resource_flags::readable
		)
	);

	typedef sge::sprite::parameters<
		sprite_choices
	> sprite_parameters;

	sprite_object my_object(
		sprite_parameters()
		.pos(
			sprite_object::vector::null()
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
		sys.keyboard_collector().key_callback(
			::input_functor(
				running
			)
		)
	);

	fcppt::signal::scoped_connection const conn_other(
		sys.mouse_collector().axis_callback(
			sprite_functor(
				my_object
			)
		)
	);

	sys.renderer().state(
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
		sys.window().dispatch();

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
