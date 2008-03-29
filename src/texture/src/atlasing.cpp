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


#include "../atlasing.hpp"
#include "../../math/rect_impl.hpp"
#include "../../math/power.hpp"

bool sge::need_atlasing(const texture::size_type s)
{
	return !math::is_power_of_2(s);
}

bool sge::need_atlasing(const texture::dim_type& dim)
{
	return !math::is_power_of_2(dim);
}

sge::texture::size_type sge::atlased_bound(const texture::size_type s)
{
	return math::is_power_of_2(s)
		? s
		: math::next_pow_2(s);
}

const sge::texture::dim_type sge::atlased_bounds(const texture::dim_type& dim)
{
	return texture::dim_type(
		atlased_bound(dim.w()),
		atlased_bound(dim.h()));
}

sge::texture::size_type sge::atlased_gap()
{
	return 1;
}

sge::texture::size_type sge::atlased_size(
	const texture::size_type s,
	const bool force_atlasing)
{
	return need_atlasing(s) || force_atlasing
		? s + 2 * atlased_gap()
		: s;
}

const sge::texture::dim_type
sge::atlased_size(
	const texture::dim_type& dim,
	const bool force_atlasing)
{
	return texture::dim_type(
		atlased_size(
			dim.w(),
			force_atlasing),
		atlased_size(
			dim.h(),
			force_atlasing));
}

const sge::texture::dim_type sge::atlased_texture_dim(const renderer_ptr rend)
{
	const texture::size_type max_size = rend->caps().max_tex_size;
	return texture::dim_type(max_size, max_size);
}

const sge::texture_ptr sge::atlased_texture(
	const renderer_ptr rend,
	const filter_args& filter)
{
	return rend->create_texture(0, atlased_texture_dim(rend), filter);
}

const sge::lock_rect sge::inner_atlased_rect(
	lock_rect outer,
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
