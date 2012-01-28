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


#include <sge/config/media_path.hpp>
#include <sge/image/colors.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/file_ptr.hpp>
#include <sge/image2d/system.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/mouse/axis_code.hpp>
#include <sge/input/mouse/axis_event.hpp>
#include <sge/input/mouse/device.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/color.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/texture/create_planar_from_view.hpp>
#include <sge/renderer/texture/planar_ptr.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/single.hpp>
#include <sge/sprite/buffers/with_declaration.hpp>
#include <sge/sprite/config/choices.hpp>
#include <sge/sprite/config/float_type.hpp>
#include <sge/sprite/config/normal_size.hpp>
#include <sge/sprite/config/texture_coordinates.hpp>
#include <sge/sprite/config/texture_level_count.hpp>
#include <sge/sprite/config/type_choices.hpp>
#include <sge/sprite/config/unit_type.hpp>
#include <sge/sprite/config/with_texture.hpp>
#include <sge/sprite/process/one.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/viewport/center_on_resize.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <ostream>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef sge::sprite::config::choices<
	sge::sprite::config::type_choices<
		sge::sprite::config::unit_type<
			int
		>,
		sge::sprite::config::float_type<
			float
		>
	>,
	sge::sprite::config::normal_size,
	boost::mpl::vector1<
		sge::sprite::config::with_texture<
			sge::sprite::config::texture_level_count<
				1u
			>,
			sge::sprite::config::texture_coordinates::normal
		>
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
			_event.code()
		)
		{
		case sge::input::mouse::axis_code::x:
			sprite_.x(
				static_cast<
					sprite_object::unit
				>(
					sprite_.x() + _event.value()
				)
			);
			break;
		case sge::input::mouse::axis_code::y:
			sprite_.y(
				static_cast<
					sprite_object::unit
				>(
					sprite_.y() + _event.value()
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
				sge::window::parameters(
					sge::window::title(
						FCPPT_TEXT("sge tutorial02")
					),
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
			sge::systems::image2d(
				sge::image::capabilities_field::null(),
				sge::media::optional_extension_set(
					fcppt::assign::make_container<
						sge::media::extension_set
					>(
						sge::media::extension(
							FCPPT_TEXT("png")
						)
					)
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
				sge::systems::cursor_option_field(
					sge::systems::cursor_option::exclusive
				)
			)
		)
	);

	typedef sge::sprite::buffers::with_declaration<
		sge::sprite::buffers::single<
			sprite_choices
		>
	> sprite_buffers_type;

	sprite_buffers_type sprite_buffers(
		sys.renderer(),
		sge::sprite::buffers::option::dynamic
	);

	sge::image2d::file_ptr const image(
		sys.image_system().load(
			sge::config::media_path()
			/ FCPPT_TEXT("images")
			/ FCPPT_TEXT("tux.png")
		)
	);

	sge::renderer::texture::planar_ptr const image_texture(
		sge::renderer::texture::create_planar_from_view(
			sys.renderer(),
			image->view(),
			sge::renderer::texture::mipmap::off(),
			sge::renderer::resource_flags::none
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
			sge::renderer::state::bool_::clear_back_buffer = true
		)
		(
			sge::renderer::state::color::back_buffer_clear_color
				= sge::image::colors::black()
		)
	);

	while(
		running
	)
	{
		sys.window_system().poll();

		sge::renderer::scoped_block const block(
			sys.renderer()
		);

		sge::sprite::process::one(
			my_object,
			sprite_buffers.buffers()
		);
	}
}
catch(
	fcppt::exception const &_exception
)
{
	fcppt::io::cerr()
		<< FCPPT_TEXT("caught sge exception: ")
		<< _exception.string()
		<< FCPPT_TEXT('\n');

	return EXIT_FAILURE;
}
catch(
	std::exception const &_exception
)
{
	std::cerr
		<< "caught std exception: "
		<< _exception.what()
		<< '\n';

	return EXIT_FAILURE;
}
