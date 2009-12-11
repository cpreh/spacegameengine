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


#include <sge/config/media_path.hpp>
#include <sge/image/multi_loader.hpp>
#include <sge/image/color/format.hpp>
#include <sge/renderer/display_mode.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <sge/sprite/choices.hpp>
#include <sge/sprite/no_color.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/with_texture.hpp>
#include <sge/sprite/type_choices.hpp>
#include <sge/sprite/intrusive/system_impl.hpp>
#include <sge/sprite/intrusive/tag.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/parameterless.hpp>
#include <sge/texture/add_image.hpp>
#include <sge/texture/default_creator_impl.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/texture/manager.hpp>
#include <sge/texture/part_fwd.hpp>
#include <sge/window/parameters.hpp>
#include <sge/text.hpp>

int main()
{
	sge::systems::instance sys(
		sge::systems::list()
		(
			sge::window::parameters(
				SGE_TEXT("sge intrusive sprite test")
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

	sge::image::multi_loader image_loader(
		sys.plugin_manager()
	);

	typedef sge::texture::default_creator<
		sge::texture::no_fragmented
	> texture_creator;
	
	texture_creator const creator(
		sys.renderer(),
		sge::image::color::format::rgba8,
		sge::renderer::filter::linear
	);

	sge::texture::manager tex_man(
		sys.renderer(),
		creator
	);

	sge::texture::const_part_ptr const
		tex1(
			sge::texture::add_image(
				tex_man,
				image_loader.load(
					sge::config::media_path()
					/ SGE_TEXT("cloudsquare.jpg")
				)
			)
		),
		tex2(
			sge::texture::add_image(
				tex_man,
				image_loader.load(
					sge::config::media_path()
					/ SGE_TEXT("grass.png")
				)
			)
		);


	typedef sge::sprite::choices<
		sge::sprite::type_choices<
			int,
			float,
			sge::sprite::no_color
		>,
		boost::mpl::vector2<
			sge::sprite::with_texture,
			sge::sprite::intrusive::tag
		>
	> sprite_choices;

	typedef sge::sprite::system<
		sprite_choices
	>::type sprite_system;

	typedef sge::sprite::object<
		sprite_choices
	> sprite_object;

	typedef sge::sprite::parameters<
		sprite_choices
	> sprite_parameters;

	sprite_system ss(
		sys.renderer()
	);

	sprite_object test(
		sprite_parameters()
		.pos(
			sprite_object::point::null()
		)
		.texture(
			tex1
		)
		.texture_size()
		.order(
			1u
		)
		.elements()
	);
}
