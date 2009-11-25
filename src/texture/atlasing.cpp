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


#include <sge/texture/atlasing.hpp>
#include <sge/renderer/caps.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/sub_data.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/image/view/sub.hpp>
#include <sge/image/view/dim.hpp>
#include <sge/math/box/basic_impl.hpp>
#include <sge/math/is_power_of_2.hpp>
#include <sge/math/next_pow_2.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/variant/object_impl.hpp>

bool sge::texture::need_atlasing(
	renderer::size_type const s)
{
	return !math::is_power_of_2(s);
}

bool sge::texture::need_atlasing(
	renderer::dim_type const &dim)
{
	return
		need_atlasing(
			dim.w())
		|| need_atlasing(
			dim.h());
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
	image::color::format::type const format,
	renderer::filter::texture const &filter)
{
	return rend->create_texture(
		atlased_texture_dim(rend),
		format,
		filter,
		renderer::resource_flags::none
	);
}

sge::renderer::lock_rect const
sge::texture::inner_atlased_rect(
	renderer::lock_rect outer,
	bool const need_atlasing_w,
	bool const need_atlasing_h
)
{
	if(need_atlasing_w)
	{
		outer.left(outer.left() + 1);
		outer.w(outer.w() - 2);
	}
	if(need_atlasing_h)
	{
		outer.top(outer.top() + 1);
		outer.h(outer.h() - 2);
	}
	return outer;
}

void sge::texture::atlas_w(
	renderer::texture_ptr const tex,
	image::view::const_object const &src,
	renderer::lock_rect const &outer_area,
	renderer::lock_rect const &inner_area)
{
	renderer::dim_type const dim(
		image::view::dim(
			src
		)
	);

	renderer::sub_data(
		tex,
		image::view::sub(
			src,
			renderer::lock_rect(
				renderer::lock_rect::pos_type::null(),
				renderer::lock_rect::dim_type(
					1,
					dim.h()
				)
			)
		),
		renderer::texture_pos_type(
			outer_area.left(),
			inner_area.top()
		)
	);

	if(inner_area.right() + 1 == outer_area.right())
		return;

	renderer::sub_data(
		tex,
		image::view::sub(
			src,
			renderer::lock_rect(
				renderer::lock_rect::pos_type(
					dim.w() - 1,
					0
				),
				renderer::lock_rect::dim_type(
					1,
					dim.h()
				)
			)
		),
		renderer::texture_pos_type(
			outer_area.right() - 1,
			inner_area.top()
		)
	);
}

void sge::texture::atlas_h(
	renderer::texture_ptr const tex,
	image::view::const_object const &src,
	renderer::lock_rect const &outer_area,
	renderer::lock_rect const &inner_area)
{
	renderer::dim_type const dim(
		image::view::dim(
			src
		)
	);

	renderer::sub_data(
		tex,
		image::view::sub(
			src,
			renderer::lock_rect(
				renderer::lock_rect::pos_type::null(),
				renderer::lock_rect::dim_type(
					dim.w(),
					1
				)
			)
		),
		renderer::texture_pos_type(
			inner_area.left(),
			outer_area.top()
		)
	);

	if(inner_area.bottom() + 1 == outer_area.bottom())
		return;

	renderer::sub_data(
		tex,
		image::view::sub(
			src,
			renderer::lock_rect(
				renderer::lock_rect::pos_type(
					0,
					dim.h() - 1
				),
				renderer::lock_rect::dim_type(
					dim.w(),
					1
				)
			)
		),
		renderer::texture_pos_type(
			inner_area.left(),
			outer_area.bottom() - 1
		)
	);
}
