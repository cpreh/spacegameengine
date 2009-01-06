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
#include <sge/renderer/device.hpp>
#include <sge/renderer/texture_util.hpp>
#include <sge/renderer/subimage_view.hpp>
#include <sge/renderer/image_view_dim.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/math/power.hpp>

bool sge::texture::need_atlasing(
	renderer::size_type const s)
{
	return !math::is_power_of_2(s);
}

bool sge::texture::need_atlasing(
	renderer::dim_type const &dim)
{
	return !math::is_power_of_2(dim);
}

sge::renderer::size_type
sge::texture::atlased_bound(
	renderer::size_type const s)
{
	return math::is_power_of_2(s)
		? s
		: math::next_pow_2(s);
}

sge::renderer::dim_type const
sge::texture::atlased_bounds(
	renderer::dim_type const &dim)
{
	return renderer::dim_type(
		atlased_bound(dim.w()),
		atlased_bound(dim.h()));
}

sge::renderer::size_type
sge::texture::atlased_gap()
{
	return 1;
}

sge::renderer::size_type
sge::texture::atlased_size(
	renderer::size_type const s,
	bool const force_atlasing)
{
	return need_atlasing(s) || force_atlasing
		? s + 2 * atlased_gap()
		: s;
}

sge::renderer::dim_type const
sge::texture::atlased_size(
	renderer::dim_type const &dim,
	bool const force_atlasing)
{
	return renderer::dim_type(
		atlased_size(
			dim.w(),
			force_atlasing),
		atlased_size(
			dim.h(),
			force_atlasing));
}

sge::renderer::dim_type const
sge::texture::atlased_texture_dim(
	renderer::device_ptr const rend)
{
	return rend->caps().max_texture_size();
}

sge::renderer::texture_ptr const
sge::texture::atlased_texture(
	renderer::device_ptr const rend,
	renderer::color_format::type const format,
	renderer::texture_filter const &filter)
{
	return rend->create_texture(
		atlased_texture_dim(rend),
		format,
		filter,
		renderer::resource_flags::none);
}

sge::renderer::lock_rect const
sge::texture::inner_atlased_rect(
	renderer::lock_rect outer,
	bool const need_atlasing_w,
	bool const need_atlasing_h)
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
	renderer::lock_rect const &outer_area,
	renderer::lock_rect const &inner_area)
{
	renderer::dim_type const dim(
		renderer::image_view_dim(
			src));

	renderer::sub_data(
		tex,
		renderer::subimage_view(
			src,
			renderer::lock_rect(
				0,
				0,
				1,
				dim.h())),
		renderer::texture_pos_type(
			outer_area.left(),
			inner_area.top()));
	
	renderer::sub_data(
		tex,
		renderer::subimage_view(
			src,
			renderer::lock_rect(
				dim.w() - 1,
				0,
				dim.w(),
				dim.h())),
		renderer::texture_pos_type(
			outer_area.right() - 1,
			inner_area.top()));
}
	
void sge::texture::atlas_h(
	renderer::texture_ptr const tex,
	renderer::const_image_view const &src,
	renderer::lock_rect const &outer_area,
	renderer::lock_rect const &inner_area)
{
	renderer::dim_type const dim(
		renderer::image_view_dim(
			src));

	renderer::sub_data(
		tex,
		renderer::subimage_view(
			src,
			renderer::lock_rect(
				0,
				0,
				dim.w(),
				1)),
		renderer::texture_pos_type(
			inner_area.left(),
			outer_area.top()));
	
	renderer::sub_data(
		tex,
		renderer::subimage_view(
			src,
			renderer::lock_rect(
				0,
				dim.h() - 1,
				dim.w(),
				dim.h())),
		renderer::texture_pos_type(
			inner_area.left(),
			outer_area.bottom() - 1));
}
