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


#include <sge/texture/part_fragmented.hpp>
#include <sge/texture/fragmented.hpp>
#include <sge/texture/atlasing.hpp>
#include <sge/renderer/sub_data.hpp>
#include <sge/math/rect/basic_impl.hpp>

sge::texture::part_fragmented::part_fragmented(
	renderer::lock_rect const &outer_area_,
	fragmented &fragment,
	bool const need_atlasing_w,
	bool const need_atlasing_h)
:
	outer_area_(outer_area_),
	fragment(fragment),
	need_atlasing_w(need_atlasing_w),
	need_atlasing_h(need_atlasing_h),
	inner_area_(
		inner_atlased_rect(
			outer_area_,
			need_atlasing_w,
			need_atlasing_h
		)
	)
{}

sge::texture::part_fragmented::~part_fragmented()
{
	fragment.return_fragment(*this);
}

void sge::texture::part_fragmented::data(
	image::view::const_object const &src)
{
	renderer::sub_data(
		texture(),
		src,
		inner_area_.pos()
	);

	if(need_atlasing_h)
		atlas_h(
			texture(),
			src,
			outer_area_,
			inner_area_
		);
	
	if(need_atlasing_w)
		atlas_w(
			texture(),
			src,
			outer_area_,
			inner_area_
		);
}

sge::renderer::lock_rect const &
sge::texture::part_fragmented::area() const
{
	return inner_area_;
}

sge::renderer::texture_ptr const
sge::texture::part_fragmented::texture()
{
	return fragment.texture();
}

sge::renderer::const_texture_ptr const
sge::texture::part_fragmented::texture() const
{
	return fragment.texture();
}

bool sge::texture::part_fragmented::repeatable() const
{
	return !need_atlasing_w && !need_atlasing_h;
}
