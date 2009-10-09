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


#include <sge/font/drawer_3d.hpp>
#include <sge/texture/rect_fragmented.hpp>
#include <sge/texture/default_creator_impl.hpp>
#include <sge/math/box/basic_impl.hpp>
#include <sge/math/dim/structure_cast.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <sge/renderer/caps.hpp>
#include <sge/image/view/dim.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/parameters.hpp>

sge::font::drawer_3d::drawer_3d(
	renderer::device_ptr const rend,
	sge::image::color::any::object const &col)
:
	rend(rend),
	col(col),
	texman(
		rend,
		texture::default_creator<
			texture::rect_fragmented
		>(
			rend,
			rend->caps().preferred_texture_format(),
			renderer::filter::linear
		)
	),
	sys(rend)
{}

sge::font::drawer_3d::~drawer_3d()
{}

void sge::font::drawer_3d::begin_rendering(
	size_type const buffer_chars,
	pos const &,
	dim const)
{
	sprites.clear();
	sprites.reserve(buffer_chars);
}

void sge::font::drawer_3d::draw_char(
	char_type const ch,
	pos const &p,
	const_image_view const &data)
{
	sge::image::dim_type const dim(
		sge::image::view::dim(
			data
		)
	);

	sprites.push_back(
		sprite::object(
			sprite::parameters()
			.pos(p)
			.texture(
				dim.content()
					? cached_texture(
						ch,
						data
					)
					: texture::const_part_ptr()
			)
			.size(
				sge::math::dim::structure_cast<
					sge::sprite::dim
				>(
					dim
				)
			)
			.color(col)
		)
	);
}

void sge::font::drawer_3d::end_rendering()
{
	sys.render(
		sprites.begin(),
		sprites.end()
	);
}

void sge::font::drawer_3d::color(
	sge::image::color::any::object const &new_color)
{
	col = new_color;
}

sge::texture::const_part_ptr const
sge::font::drawer_3d::cached_texture(
	char_type const ch,
	const_image_view const &data)
{
	texture_map::const_iterator const it(
		textures.find(ch)
	);

	return it != textures.end()
		? it->second
		: textures.insert(
			std::make_pair(
				ch,
				texman.add(
					data
				)
			)
		).first->second;
}
