/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/math/rect_impl.hpp>
#include <sge/renderer/colors.hpp>
#include <sge/renderer/image.hpp>
#include <boost/gil/algorithm.hpp>

namespace
{

struct converter {
	void operator()(
		sge::font::color const src,
		sge::renderer::rgba8_color &dest) const;
};

}

sge::font::drawer_3d::drawer_3d(
	renderer::device_ptr const rend,
	renderer::any_color const &col)
:
	rend(rend),
	col(col),
	texman(
		rend,
		texture::default_creator<texture::rect_fragmented>(
			rend,
			renderer::color_format::rgba8, // TODO
			renderer::linear_filter)),
	sys(rend)
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
	dim const d(
		gil_dim_to_sge(
			data.dimensions()));

	sprites.push_back(
		sprite::object(
			p,
			d.content()
				? cached_texture(
					ch,
					data)
				: texture::part_ptr(),
			d,
			col));
}

void sge::font::drawer_3d::end_rendering()
{
	sys.render(sprites.begin(), sprites.end());
}

void sge::font::drawer_3d::set_color(
	renderer::any_color const &new_color)
{
	col = new_color;
}

sge::texture::part_ptr const
sge::font::drawer_3d::cached_texture(
	char_type const ch,
	const_image_view const &data)
{
	texture_map::const_iterator const it = textures.find(ch);
	if(it != textures.end())
		return it->second;
	
	// TODO: somehow use the renderer's preferred color format here and avoid conversions!
	renderer::rgba8_image img(
		data.width(),
		data.height());

	{
		converter conv;
		boost::gil::copy_and_convert_pixels(
			data,
			boost::gil::view(img),
			conv);
	}

	return textures.insert(
		std::make_pair(
			ch,
			texman.add(
				renderer::const_image_view(
					boost::gil::const_view(
						img)
		)))).first->second;
}

namespace
{

void converter::operator()(
	sge::font::color const src,
	sge::renderer::rgba8_color &dest) const
{
	dest = sge::renderer::rgba8_color(
		255,
		255,
		255,
		src);
}

}
