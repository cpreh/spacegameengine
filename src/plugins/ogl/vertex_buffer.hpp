/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_OGL_VERTEX_BUFFER_HPP_INCLUDED
#define SGE_OGL_VERTEX_BUFFER_HPP_INCLUDED

#include "../../renderer/vertex_buffer.hpp"
#include "basic_arb_buffer.hpp"
#include "vertex_format.hpp"

namespace sge
{
namespace ogl
{

class vertex_buffer : public basic_arb_buffer<sge::vertex_buffer,GL_ARRAY_BUFFER_ARB> {
public:
	vertex_buffer(size_type size, const sge::vertex_format& format, resource_flag_t flags, const_pointer src);

	size_type stride() const;
	const sge::vertex_format& get_vertex_format() const;
	iterator create_iterator(pointer p);
	const_iterator create_iterator(const_pointer p) const;
	iterator begin();
	const_iterator begin() const;

	void set_format();
private:
	sge::vertex_format format;
	vertex_format ogl_format;
};

}
}

#endif
