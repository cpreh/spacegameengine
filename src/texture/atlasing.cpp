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
#include <sge/math/rect_impl.hpp>
#include <sge/math/power.hpp>

bool sge::need_atlasing(
	const renderer::texture::size_type s)
{
	return !math::is_power_of_2(s);
}

bool sge::need_atlasing(const renderer::texture::dim_type& dim)
{
	return !math::is_power_of_2(dim);
}

sge::renderer::texture::size_type
sge::atlased_bound(
	const renderer::texture::size_type s)
{
	return math::is_power_of_2(s)
		? s
		: math::next_pow_2(s);
}

const sge::renderer::texture::dim_type
sge::atlased_bounds(
	const renderer::texture::dim_type& dim)
{
	return renderer::texture::dim_type(
		atlased_bound(dim.w()),
		atlased_bound(dim.h()));
}

sge::renderer::texture::size_type sge::atlased_gap()
{
	return 1;
}

sge::renderer::texture::size_type sge::atlased_size(
	const renderer::texture::size_type s,
	const bool force_atlasing)
{
	return need_atlasing(s) || force_atlasing
		? s + 2 * atlased_gap()
		: s;
}

const sge::renderer::texture::dim_type
sge::atlased_size(
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
sge::atlased_texture_dim(
	const renderer::device_ptr rend)
{
	const renderer::texture::size_type max_size = rend->get_caps().max_tex_size;
	return renderer::texture::dim_type(max_size, max_size);
}

const sge::renderer::texture_ptr
sge::atlased_texture(
	const renderer::device_ptr rend,
	const renderer::filter_args& filter)
{
	// FIXME:
	//return rend->create_texture(0, atlased_texture_dim(rend), filter);
}

const sge::renderer::lock_rect
sge::inner_atlased_rect(
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
