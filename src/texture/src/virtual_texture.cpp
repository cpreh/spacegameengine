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


#include <iostream>
#include <ostream>
#include "../virtual_texture.hpp"
#include "../fragmented_texture.hpp"
#include "../atlasing.hpp"
#include "../../renderer/transform.hpp"
#include "../../math/utility.hpp"
#include "../../math/rect_impl.hpp"

sge::virtual_texture::virtual_texture(const lock_rect& outer_area_, fragmented_texture& fragment, const bool repeatable_)
: outer_area_(outer_area_),
   fragment(fragment),
   repeatable_(repeatable_),
   inner_area_(repeatable_ ? outer_area_ : inner_atlased_rect(outer_area()))
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
		std::cerr << "Warning: texture not repeatable but repetition is " << repeat << "!\n";

	const texture_ptr tex = my_texture();
	return tex ? tex_size_to_space_rect(area(), tex->width(), tex->height(), repeat) : math::rect();
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
	return repeatable_;
}

void sge::virtual_texture::set_data(const texture::const_pointer src)
{
	my_texture()->set_data(src, inner_area_);

	// FIXME
	// apply atlasing fix
	if(!repeatable())
	{
//		my_texture()->set_data(src, lock_rect(outer_area().left, outer_area().top, outer_area().right, outer_area().top + 1));
//		my_texture()->set_data(src + width(area()) * (height(area()) - 1), lock_rect(outer_area().left, outer_area().top, outer_area().right, outer_area().top + 1));
	}
}
