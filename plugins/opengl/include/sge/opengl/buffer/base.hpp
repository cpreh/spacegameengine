/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_OPENGL_BUFFER_BASE_HPP_INCLUDED
#define SGE_OPENGL_BUFFER_BASE_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/buffer/base_fwd.hpp>
#include <sge/opengl/buffer/id.hpp>
#include <sge/opengl/buffer/optional_id_fwd.hpp>
#include <sge/opengl/buffer/type.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace buffer
{

class base
{
	FCPPT_NONCOPYABLE(
		base
	);
protected:
	base();
public:
	virtual
	~base();

	virtual
	sge::opengl::buffer::id
	gen_buffer() = 0;

	virtual
	void
	delete_buffer(
		sge::opengl::buffer::id
	) = 0;

	virtual
	void
	bind_buffer(
		sge::opengl::buffer::optional_id const &
	) = 0;

	virtual
	GLvoid *
	map_buffer(
		GLenum flags
	) = 0;

	virtual
	GLvoid *
	map_buffer_range(
		GLenum flags,
		GLsizei first,
		GLsizei size
	) = 0;

	virtual
	bool
	map_buffer_range_supported() const = 0;

	virtual
	void
	unmap_buffer() = 0;

	virtual
	void
	buffer_data(
		GLsizei size,
		GLvoid const *data,
		GLenum flags
	) = 0;

	virtual
	void
	buffer_sub_data(
		GLsizei first,
		GLsizei size,
		GLvoid const *data
	) = 0;

	virtual
	GLvoid *
	buffer_offset(
		GLsizei offset
	) const = 0;

	virtual
	bool
	native() const = 0;
};

}
}
}

#endif
