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


#ifndef SGE_OPENGL_PBO_HPP_INCLUDED
#define SGE_OPENGL_PBO_HPP_INCLUDED

#include "../../renderer/texture_base.hpp"
#include "basic_raw_buffer.hpp"
#include "common.hpp"

namespace sge
{
namespace ogl
{

struct pbo_base {
	typedef texture_base::size_type              size_type;
	typedef texture_base::difference_type        difference_type;
	typedef texture_base::value_type             value_type;
	typedef texture_base::reference              reference;
	typedef texture_base::const_reference        const_reference;
	typedef texture_base::pointer                pointer;
	typedef texture_base::const_pointer          const_pointer;
	typedef texture_base::iterator               iterator;
	typedef texture_base::const_iterator         const_iterator;
	typedef texture_base::reverse_iterator       reverse_iterator;
	typedef texture_base::const_reverse_iterator const_reverse_iterator;
};

const GLenum pixel_pack_buffer_type = GL_PIXEL_PACK_BUFFER_ARB,
             pixel_unpack_buffer_type = GL_PIXEL_UNPACK_BUFFER_ARB;

typedef basic_raw_buffer<pbo_base, pixel_pack_buffer_type>   pixel_pack_buffer;
typedef basic_raw_buffer<pbo_base, pixel_unpack_buffer_type> pixel_unpack_buffer;

}
}

#endif
