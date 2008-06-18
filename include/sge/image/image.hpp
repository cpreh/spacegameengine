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


#ifndef SGE_IMAGE_IMAGE_HPP_INCLUDED
#define SGE_IMAGE_IMAGE_HPP_INCLUDED

#include "../shared_ptr.hpp"
#include "../path.hpp"
#include "../renderer/types.hpp"
#include "../renderer/color.hpp"
#include "../math/dim.hpp"
#include <boost/noncopyable.hpp>
#include <cstddef>

namespace sge
{
namespace image
{

class image : boost::noncopyable {
public:
	typedef std::size_t                   size_type;
	typedef math::basic_dim<size_type, 2> dim_type;
	typedef renderer::color               value_type;
	typedef value_type*                   pointer;
	typedef const value_type*             const_pointer;

	virtual void data(const_pointer, const dim_type&) = 0;
	virtual const_pointer data() const = 0;
	virtual dim_type dim() const = 0;
	virtual size_type width() const = 0;
	virtual size_type height() const = 0;
	virtual void resample(const dim_type&) = 0;
	virtual void save(const path&) = 0;
	virtual ~image(){}
};

typedef shared_ptr<image> image_ptr;

}
}

#endif
