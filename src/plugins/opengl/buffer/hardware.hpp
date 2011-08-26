/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_BUFFER_HARDWARE_HPP_INCLUDED
#define SGE_OPENGL_BUFFER_HARDWARE_HPP_INCLUDED

#include "base.hpp"
#include "id.hpp"
#include "../common.hpp"
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opengl
{
namespace buffer
{

class hardware
:
	public buffer::base
{
	FCPPT_NONCOPYABLE(
		hardware
	);
public:
	hardware();

	~hardware();
private:
	buffer::id const
	gen_buffer();

	void
	delete_buffer(
		buffer::id
	);

	void
	bind_buffer(
		GLenum type,
		buffer::id
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

	bool const
		have_version_1_5_,
		have_arb_;

	PFNGLGENBUFFERSPROC const gl_gen_buffers_;

	PFNGLDELETEBUFFERSPROC const gl_delete_buffers_;

	PFNGLBINDBUFFERPROC const gl_bind_buffer_;

	PFNGLMAPBUFFERPROC const gl_map_buffer_;

	PFNGLUNMAPBUFFERPROC const gl_unmap_buffer_;

	PFNGLBUFFERDATAPROC const gl_buffer_data_;

	PFNGLBUFFERSUBDATAPROC const gl_buffer_sub_data_;

	PFNGLMAPBUFFERRANGEPROC const gl_map_buffer_range_;
};

}
}
}

#endif
