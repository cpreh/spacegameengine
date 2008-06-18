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


#include <sge/texture/part_fragmented.hpp>
#include <sge/texture/fragmented.hpp>
#include <sge/texture/atlasing.hpp>

sge::texture::part_fragmented::part_fragmented(
	const renderer::lock_rect& outer_area_,
	fragmented &fragment,
	const bool need_atlasing_w,
	const bool need_atlasing_h)
: outer_area_(outer_area_),
   fragment(fragment),
   need_atlasing_w(need_atlasing_w),
   need_atlasing_h(need_atlasing_h),
   inner_area_(
   	inner_atlased_rect(
	   	outer_area_,
		need_atlasing_w,
		need_atlasing_h))
{}

sge::texture::part_fragmented::~part_fragmented()
{
	fragment.return_fragment(*this);
}

void sge::texture::part_fragmented::data(
	renderer::const_image_view const &src)
{
	my_texture()->sub_data(src, inner_area_);

	if(need_atlasing_h)
		atlas_h(my_texture(), src, outer_area_);
	if(need_atlasing_w)
		atlas_w(my_texture(), src, outer_area_);
}

const sge::renderer::lock_rect&
sge::texture::part_fragmented::area() const
{
	return inner_area_;
}

const sge::renderer::texture_ptr
sge::texture::part_fragmented::my_texture() const
{
	return fragment.get_texture();
}

bool sge::texture::part_fragmented::repeatable() const
{
	return !need_atlasing_w && !need_atlasing_h;
}
