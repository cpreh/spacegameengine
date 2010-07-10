/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_SOFTWARE_VBO_HPP_INCLUDED
#define SGE_OPENGL_SOFTWARE_VBO_HPP_INCLUDED

#include "common.hpp"
#include "vbo_base.hpp"

namespace sge
{
namespace opengl
{

class software_vbo : public vbo_base {
public:
	GLuint gen_buffer();

	void
	delete_buffer(
		GLuint
	);

	void
	bind_buffer(
		GLenum type,
		GLuint
	);

	GLvoid *
	map_buffer(
		GLenum type,
		GLenum flags
	);

	GLvoid *
	map_buffer_range(
		GLenum type,
		GLenum flags,
		GLsizei first,
		GLsizei size
	);

	bool
	map_buffer_range_supported() const;

	void
	unmap_buffer(
		GLenum type
	);

	void
	buffer_data(
		GLenum type,
		GLsizei size,
		GLvoid const *data,
		GLenum flags
	);

	void
	buffer_sub_data(
		GLenum type,
		GLsizei first,
		GLsizei size,
		GLvoid const *data
	);

	void *
	buffer_offset(
		GLenum type,
		GLsizei offset
	) const;

	bool
	hardware_supported() const;

	static GLenum
	unique_id();
};

}
}

#endif
