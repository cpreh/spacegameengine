/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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

#include <sge/opengl/common.hpp>
#include <sge/opengl/buffer/base.hpp>
#include <sge/opengl/buffer/id.hpp>
#include <sge/opengl/buffer/optional_id_fwd.hpp>
#include <sge/opengl/buffer/type.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace buffer
{

class hardware
:
	public sge::opengl::buffer::base
{
	FCPPT_NONCOPYABLE(
		hardware
	);
public:
	hardware();

	~hardware()
	override;
private:
	sge::opengl::buffer::id const
	gen_buffer()
	override;

	void
	delete_buffer(
		sge::opengl::buffer::id
	)
	override;

	void
	bind_buffer(
		sge::opengl::buffer::type,
		sge::opengl::buffer::optional_id const &
	)
	override;

	GLvoid *
	map_buffer(
		sge::opengl::buffer::type,
		GLenum flags
	)
	override;

	GLvoid *
	map_buffer_range(
		sge::opengl::buffer::type,
		GLenum flags,
		GLsizei first,
		GLsizei size
	)
	override;

	bool
	map_buffer_range_supported() const
	override;

	void
	unmap_buffer(
		sge::opengl::buffer::type
	)
	override;

	void
	buffer_data(
		sge::opengl::buffer::type,
		GLsizei size,
		GLvoid const *data,
		GLenum flags
	)
	override;

	void
	buffer_sub_data(
		sge::opengl::buffer::type,
		GLsizei first,
		GLsizei size,
		GLvoid const *data
	)
	override;

	void *
	buffer_offset(
		sge::opengl::buffer::type,
		GLsizei offset
	) const
	override;

	bool
	hardware_supported() const
	override;

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

	typedef std::map<
		sge::opengl::buffer::type,
		sge::opengl::buffer::id
	> bound_buffer_map;

	bound_buffer_map bound_buffers_;
};

}
}
}

#endif
