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


#ifndef SGE_DEVIL_IMAGE_HPP_INCLUDED
#define SGE_DEVIL_IMAGE_HPP_INCLUDED

#include "../../path.hpp"
#include "../../image/image.hpp"
#include "../../image/image_format.hpp"
#include "image_impl.hpp"

namespace sge
{
namespace devil
{

class image : public sge::image {
public:
	explicit image(const path&);
	image(image_format::type type, const_pointer format_data, size_type size);
	image(const_pointer p, const dim_type&);
	const_pointer data() const;
	void data(const_pointer, const dim_type&);
	dim_type dim() const;
	size_type width() const;
	size_type height() const;
	void resample(const dim_type&);
	void save(const path&);
private:
	void bind_me() const;
	image_impl impl;
};

}
}

#endif

