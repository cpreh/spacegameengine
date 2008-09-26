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


#include <sge/texture/atlasing.hpp>
#include <sge/renderer/caps.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/math/power.hpp>

bool sge::texture::need_atlasing(
	const renderer::texture::size_type s)
{
	return !math::is_power_of_2(s);
}

bool sge::texture::need_atlasing(
	const renderer::texture::dim_type& dim)
{
	return !math::is_power_of_2(dim);
}

sge::renderer::texture::size_type
sge::texture::atlased_bound(
	const renderer::texture::size_type s)
{
	return math::is_power_of_2(s)
		? s
		: math::next_pow_2(s);
}

const sge::renderer::texture::dim_type
sge::texture::atlased_bounds(
	const renderer::texture::dim_type& dim)
{
	return renderer::texture::dim_type(
		atlased_bound(dim.w()),
		atlased_bound(dim.h()));
}

sge::renderer::texture::size_type
sge::texture::atlased_gap()
{
	return 1;
}

sge::renderer::texture::size_type
sge::texture::atlased_size(
	const renderer::texture::size_type s,
	const bool force_atlasing)
{
	return need_atlasing(s) || force_atlasing
		? s + 2 * atlased_gap()
		: s;
}

const sge::renderer::texture::dim_type
sge::texture::atlased_size(
	const renderer::texture::dim_type& dim,
	const bool force_atlasing)
{
	return renderer::texture::dim_type(
		atlased_size(
			dim.w(),
			force_atlasing),
		atlased_size(
			dim.h(),
			force_atlasing));
}

const sge::renderer::texture::dim_type
sge::texture::atlased_texture_dim(
	const renderer::device_ptr rend)
{
	const renderer::texture::size_type max_size = rend->get_caps().max_tex_size;
	return renderer::texture::dim_type(max_size, max_size);
}

sge::renderer::texture_ptr const
sge::texture::atlased_texture(
	renderer::device_ptr const rend,
	renderer::filter_args const &filter)
{
	return rend->create_texture(
		atlased_texture_dim(rend),
		renderer::color_format::rgba8,
		filter,
		renderer::resource_flags::none);
}

const sge::renderer::lock_rect
sge::texture::inner_atlased_rect(
	renderer::lock_rect outer,
	const bool need_atlasing_w,
	const bool need_atlasing_h)
{
	if(need_atlasing_w)
	{
		++outer.left();
		--outer.right();
	}
	if(need_atlasing_h)
	{
		++outer.top();
		--outer.bottom();
	}
	return outer;
}

void sge::texture::atlas_w(
	renderer::texture_ptr const tex,
	renderer::const_image_view const &src,
	renderer::lock_rect const &outer_area)
{
	// FIXME: use a gil image here
	/*typedef std::vector<renderer::texture::value_type> pixel_vector;
	pixel_vector height_pixels(outer_area().h());

	height_pixels.front() = *src;
	for(pixel_vector::size_type h = 1; h < height_pixels.size() - 1; ++h)
		height_pixels[h] = *(src + area().w() * h);
	height_pixels.back() = *(src + area().w() * (area().h() - 1));

	my_texture()->set_data(
		height_pixels.data(),
		renderer::lock_rect(
			outer_area().left(),
			outer_area().top(),
			outer_area().left() + 1,
			outer_area().bottom()));

	height_pixels.front() = *(src + area().w() - 1); 
	for(pixel_vector::size_type h = 1; h < height_pixels.size() - 1; ++h)
		height_pixels[h] = *(src + area().w() * (h + 1) - 1);
	height_pixels.back() = *(src + area().w() * area().h() - 1);

	my_texture()->set_data(
		height_pixels.data(),
	        renderer::lock_rect(
			outer_area().right() - 1,
			outer_area().top(),
			outer_area().right(),
			outer_area().bottom()));*/
}
	
void sge::texture::atlas_h(
	renderer::texture_ptr const tex,
	renderer::const_image_view const &src,
	renderer::lock_rect const &outer_area)
{
	// FIXME: use a GIL view here!
	/*tex->sub_data(
		src,
	        renderer::lock_rect(
			outer_area.left() + 1,
			outer_area.top(),
			outer_area.right() - 1,
			outer_area.top() + 1));
	tex->sub_data(
		src + area().w() * (area().h() - 1),
		renderer::lock_rect(
			outer_area().left() + 1,
			outer_area().bottom() - 1,
			outer_area().right() - 1,
			outer_area().bottom()));*/
}
