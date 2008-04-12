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


#include <sge/texture/virtual_texture.hpp>
#include <sge/texture/fragmented_texture.hpp>
#include <sge/texture/atlasing.hpp>
#include <sge/raw_vector_impl.hpp>
#include <sge/renderer/transform.hpp>
#include <sge/math/compare.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/iostream.hpp>
#include <ostream>

sge::virtual_texture::virtual_texture(
	const lock_rect& outer_area_,
	fragmented_texture& fragment,
	const bool need_atlasing_w,
	const bool need_atlasing_h)
: outer_area_(outer_area_),
   fragment(fragment),
   need_atlasing_w(need_atlasing_w),
   need_atlasing_h(need_atlasing_h),
   inner_area_(
   	inner_atlased_rect(
	   	outer_area(),
		need_atlasing_w,
		need_atlasing_h))
{}

sge::virtual_texture::~virtual_texture()
{
	fragment.return_fragments(*this);
}

const sge::lock_rect& sge::virtual_texture::area() const
{
	return inner_area_;
}

const sge::lock_rect& sge::virtual_texture::outer_area() const
{
	return outer_area_;
}

const sge::math::rect sge::virtual_texture::area_texc(const space_unit repeat) const
{
	if(!math::compare(repeat, static_cast<space_unit>(1)) && repeatable() == false)
		sge::cerr << SGE_TEXT("Warning: texture not repeatable but repetition is ") << repeat << SGE_TEXT("!\n");

	const texture_ptr tex = my_texture();
	return tex ? tex_size_to_space_rect(area(), tex->dim(), repeat) : math::rect();
}

const sge::tex_pos sge::virtual_texture::translate(const tex_pos &local_coords, const space_unit repeat) const
{
	const sge::math::rect texc = area_texc(repeat);
	return sge::tex_pos(
		(1 - local_coords[0]) * texc.left() + local_coords[0] * texc.right(),
		(1 - local_coords[1]) * texc.top() + local_coords[1] * texc.bottom()
	);
}

const sge::tex_pos sge::virtual_texture::translate(const tex_pos::value_type x, const tex_pos::value_type y, const space_unit repeat) const
{
	return translate(sge::tex_pos(x, y), repeat);
}

const sge::texture_ptr sge::virtual_texture::my_texture() const
{
	return fragment.get_texture();
}

bool sge::virtual_texture::repeatable() const
{
	return !need_atlasing_w && !need_atlasing_h;
}

void sge::virtual_texture::set_data(const texture::const_pointer src)
{
	my_texture()->set_data(src, inner_area_);

	if(need_atlasing_h)
	{
		my_texture()->set_data(src,
	        	               lock_rect(outer_area().left() + 1, outer_area().top(), outer_area().right() - 1, outer_area().top() + 1));
		my_texture()->set_data(src + area().w() * (area().h() - 1),
		                       lock_rect(outer_area().left() + 1, outer_area().bottom() - 1, outer_area().right() - 1, outer_area().bottom()));
	}

	if(need_atlasing_w)
		return;
	
	typedef raw_vector<texture::value_type> pixel_vector;
	pixel_vector height_pixels(outer_area().h());

	height_pixels.front() = *src;
	for(pixel_vector::size_type h = 1; h < height_pixels.size() - 1; ++h)
		height_pixels[h] = *(src + area().w() * h);
	height_pixels.back() = *(src + area().w() * (area().h() - 1));

	my_texture()->set_data(height_pixels.data(),
	                       lock_rect(outer_area().left(), outer_area().top(), outer_area().left() + 1, outer_area().bottom()));

	height_pixels.front() = *(src + area().w() - 1); 
	for(pixel_vector::size_type h = 1; h < height_pixels.size() - 1; ++h)
		height_pixels[h] = *(src + area().w() * (h + 1) - 1);
	height_pixels.back() = *(src + area().w() * area().h() - 1);

	my_texture()->set_data(height_pixels.data(),
	                       lock_rect(outer_area().right() - 1, outer_area().top(), outer_area().right(), outer_area().bottom()));
}
