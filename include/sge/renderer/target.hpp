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


#ifndef SGE_RENDERER_TARGET_HPP_INCLUDED
#define SGE_RENDERER_TARGET_HPP_INCLUDED

#include "dim_types.hpp"
#include "size_type.hpp"
#include "image_view.hpp"
#include "../export.hpp"
#include <boost/noncopyable.hpp>
#include <cstddef>

namespace sge
{
namespace renderer
{

class SGE_CLASS_SYMBOL target : boost::noncopyable {
public:
	typedef renderer::size_type          size_type;
	typedef renderer::dim_type           dim_type;
	typedef lock_rect                    rect_type;

	SGE_SYMBOL const_image_view const
	lock() const;

	virtual const_image_view const
	lock(
		lock_rect const &dest) const = 0;

	virtual void unlock() const = 0;

	virtual dim_type const dim() const = 0;
	SGE_SYMBOL rect_type const rect() const;
	SGE_SYMBOL size_type size() const;
	
	SGE_SYMBOL virtual ~target();
};

}
}

#endif
