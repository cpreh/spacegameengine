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


#ifndef SGE_RENDERER_TEXTURE_BASE_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_BASE_HPP_INCLUDED

#include "resource_flags.hpp"
#include "lock_flags.hpp"
#include "../shared_ptr.hpp"
#include "../math/rect.hpp"
#include <iterator>
#include <cstddef>

namespace sge
{
namespace renderer
{

class texture_base {
public:
	typedef std::size_t                           size_type;
	typedef std::ptrdiff_t                        difference_type;
	typedef resource_flag_t                       resource_flag_type;
	typedef lock_flag_t                           lock_flag_type;

	virtual ~texture_base() {}
	virtual size_type content() const = 0;
	virtual resource_flag_type flags() const = 0;
};

typedef shared_ptr<texture_base>                  texture_base_ptr;

}
}

#endif
