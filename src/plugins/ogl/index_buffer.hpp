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


#ifndef SGE_OGL_INDEX_BUFFER_HPP_INCLUDED
#define SGE_OGL_INDEX_BUFFER_HPP_INCLUDED

#include "../../renderer/index_buffer.hpp"
#include "common.hpp"
#include "basic_buffer.hpp"

namespace sge
{
namespace ogl
{

class index_buffer : public basic_buffer<sge::index_buffer,GL_ELEMENT_ARRAY_BUFFER> {
	typedef basic_buffer<sge::index_buffer,GL_ELEMENT_ARRAY_BUFFER> base;
public:
	index_buffer(size_type sz, resource_flag_t flags, const_pointer src);
	iterator begin();
	const_iterator begin() const;
	static void unbind();
};

}
}

#endif

