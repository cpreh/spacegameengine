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


#ifndef SGE_RENDERER_VOLUME_TEXTURE_HPP_INCLUDED
#define SGE_RENDERER_VOLUME_TEXTURE_HPP_INCLUDED

#include "../export.hpp"
#include "../math/dim.hpp"
#include "../math/box.hpp"
#include "texture_base.hpp"

namespace sge
{
namespace renderer
{

typedef math::basic_box<texture_base::size_type> lock_box;

class volume_texture : public texture_base {
public:
	typedef math::basic_dim<size_type, 3> box_type;

	SGE_SYMBOL size_type size() const;
	virtual const box_type box() const = 0;
	virtual void set_data(const_pointer p) = 0;
	virtual void set_data(const_pointer p, const lock_box&) = 0;
};

typedef shared_ptr<volume_texture> volume_texture_ptr;

}
}

#endif
