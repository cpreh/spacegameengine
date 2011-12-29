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


#include <sge/exception.hpp>
#include <sge/config/media_path.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/file_ptr.hpp>
#include <sge/image2d/system.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/texture/address_mode2.hpp>
#include <sge/renderer/texture/create_planar_from_view.hpp>
#include <sge/renderer/texture/planar_ptr.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/sprite/choices.hpp>
#include <sge/sprite/external_system_impl.hpp>
#include <sge/sprite/no_color.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/sprite/render_one.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/type_choices.hpp>
#include <sge/sprite/with_dim.hpp>
#include <sge/sprite/with_texture.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/viewport/center_on_resize.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <ostream>
#include <fcppt/config/external_end.hpp>


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
						FCPPT_TEXT("sge tutorial01")
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
	);

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
			sge::renderer::texture::address_mode2(
				sge::renderer::texture::address_mode::clamp
			),
			sge::renderer::resource_flags::none
		)
	);

	sprite_object const my_object(
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

	for (;;)
	{
		sys.window_system().poll();

		sge::renderer::scoped_block const block_(
			sys.renderer()
		);

		sge::sprite::render_one(
			ss,
			my_object
		);
	}
}
catch(
	sge::exception const &e
)
{
	fcppt::io::cerr()
		<< FCPPT_TEXT("caught sge exception: ")
		<< e.string()
		<< FCPPT_TEXT('\n');

	return EXIT_FAILURE;
}
catch(
	std::exception const &e
)
{
	std::cerr
		<< "caught std exception: "
		<< e.what()
		<< '\n';
	return EXIT_FAILURE;
}
