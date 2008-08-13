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


#ifndef SGE_RENDERER_TEXTURE_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_HPP_INCLUDED

#include "../export.hpp"
#include "../math/dim.hpp"
#include "texture_base.hpp"
#include "image_view.hpp"
#include "types.hpp" // FIXME

namespace sge
{
namespace renderer
{

class texture : public texture_base {
public:
	typedef math::basic_vector<size_type, 2>     pos_type;
	typedef math::basic_dim<size_type, 2>        dim_type;
	typedef lock_rect                            rect_type;

	virtual dim_type const dim() const = 0;
	
	image_view const lock(lock_flag_t);
	const_image_view const lock() const;

	virtual image_view const lock(lock_rect const &, lock_flag_t) = 0;
	virtual const_image_view const lock(lock_rect const &) const = 0;

	virtual void unlock() const = 0;
	size_type size() const;
	rect_type const rect() const;

	size_type content() const;
};

const texture::dim_type gil_dim_to_sge(image_view::point_t const &);
//const image_view::point_t sge_dim_to_gil(texture::dim_type const &);

typedef shared_ptr<texture> texture_ptr;
typedef shared_ptr<texture const> const_texture_ptr;

}
}

#endif
