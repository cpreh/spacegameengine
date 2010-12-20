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


#include "../depth_stencil_texture.hpp"
#include "../common.hpp"
#include "../convert/depth_stencil_to_format.hpp"
#include "../convert/depth_stencil_to_format_type.hpp"
#include "../convert/depth_stencil_to_internal_format.hpp"
#include "../texfuncs/bind.hpp"
#include "../texfuncs/set.hpp"
#include "../texfuncs/set_filter.hpp"
#include <sge/renderer/filter/point.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>

#include "../texfuncs/get_image.hpp"
#include <mizuiro/image/store.hpp>
#include <mizuiro/image/format.hpp>
#include <mizuiro/image/dimension.hpp>
#include <mizuiro/image/interleaved.hpp>
#include <mizuiro/image/raw_view.hpp>
#include <mizuiro/image/underlying_data_pointer.hpp>
#include <mizuiro/color/homogenous.hpp>
#include <mizuiro/color/layout/alpha.hpp>
#include <mizuiro/access/raw.hpp>

#include <iostream>

sge::opengl::depth_stencil_texture::depth_stencil_texture(
	opengl::context::object &_context,
	dim_type const &_dim,
	renderer::depth_stencil_format::type const _format
)
:
	renderer::depth_stencil_texture(),
	opengl::texture_base(
		GL_TEXTURE_2D
	),
	holder_(),
	dim_(_dim),
	format_(
		convert::depth_stencil_to_format(
			_format
		)
	),
	format_type_(
		convert::depth_stencil_to_format_type(
			_format
		)
	)
{
	bind_me();

	sge::renderer::filter::texture const filter(
		sge::renderer::filter::point
	);

	texfuncs::set_filter(
		_context,
		type(),
		filter
	);

	texfuncs::set(
		_context,
		type(),
		format_,
		format_type_,
		convert::depth_stencil_to_internal_format(
			_format
		),
		filter,
		dim(),
		0
	);
}

sge::opengl::depth_stencil_texture::~depth_stencil_texture()
{
}

GLuint
sge::opengl::depth_stencil_texture::id() const
{
	return holder_.id();
}

void
sge::opengl::depth_stencil_texture::bind_me() const
{
	texfuncs::bind(
		type(),
		id()
	);
}

sge::opengl::depth_stencil_texture::dim_type const
sge::opengl::depth_stencil_texture::dim() const
{
	return dim_;
}

sge::renderer::resource_flags_field const
sge::opengl::depth_stencil_texture::flags() const
{
	return renderer::resource_flags::none;
}

#include <iostream>

void
sge::opengl::depth_stencil_texture::debug()
{
	typedef mizuiro::image::format<
		mizuiro::image::dimension<
			2
		>,
		mizuiro::image::interleaved<
			mizuiro::color::homogenous<
				float,
				mizuiro::color::layout::alpha
			>
		>
	> format;

	typedef mizuiro::image::store<
		format,
		mizuiro::access::raw
	> store;

	store img(
		store::dim_type(
			dim().w(),
			dim().h()
		)
	);

	bind_me();

	texfuncs::get_image(
		type(),
		format_,
		format_type_,
		mizuiro::image::underlying_data_pointer(
			img.view()
		)
	);

	store::view_type const view(
		img.view());

	std::cout << "P2\n";
	std::cout << dim().w() << " " << dim().h() << "\n";
	std::cout << "255" << "\n";

	for(
		store::view_type::iterator it(
			view.begin()
		);
		it != view.end();
		++it
	)
		std::cout << 
			static_cast<int>((*it).get<mizuiro::color::channel::alpha>()*255) << " ";
}
