/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_BUFFER_SOFTWARE_HPP_INCLUDED
#define SGE_OPENGL_BUFFER_SOFTWARE_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/buffer/base.hpp>
#include <sge/opengl/buffer/id.hpp>
#include <sge/opengl/buffer/optional_id.hpp>
#include <sge/opengl/buffer/type.hpp>
#include <sge/renderer/raw_pointer.hpp>
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

class software
:
	public sge::opengl::buffer::base
{
	FCPPT_NONCOPYABLE(
		software
	);
public:
	software();

	~software();
private:
	sge::opengl::buffer::id const
	gen_buffer();

	void
	delete_buffer(
		sge::opengl::buffer::id
	);

	void
	bind_buffer(
		sge::opengl::buffer::type,
		sge::opengl::buffer::optional_id const &
	);

	GLvoid *
	map_buffer(
		sge::opengl::buffer::type,
		GLenum flags
	);

	GLvoid *
	map_buffer_range(
		sge::opengl::buffer::type,
		GLenum flags,
		GLsizei first,
		GLsizei size
	);

	bool
	map_buffer_range_supported() const;

	void
	unmap_buffer(
		sge::opengl::buffer::type
	);

	void
	buffer_data(
		sge::opengl::buffer::type,
		GLsizei size,
		GLvoid const *data,
		GLenum flags
	);

	void
	buffer_sub_data(
		sge::opengl::buffer::type,
		GLsizei first,
		GLsizei size,
		GLvoid const *data
	);

	void *
	buffer_offset(
		sge::opengl::buffer::type,
		GLsizei offset
	) const;

	bool
	hardware_supported() const;

	typedef std::map<
		sge::opengl::buffer::id,
		sge::renderer::raw_pointer
	> buffer_map;

	sge::opengl::buffer::id const
	bound_buffer(
		sge::opengl::buffer::type
	) const;

	buffer_map::iterator
	buffer_object(
		sge::opengl::buffer::id
	);

	buffer_map::const_iterator
	buffer_object(
		sge::opengl::buffer::id
	) const;

	typedef std::map<
		sge::opengl::buffer::type,
		sge::opengl::buffer::optional_id
	> bound_buffer_map;

	bound_buffer_map bound_buffers_;

	sge::opengl::buffer::id nextid_;

	buffer_map buffers_;
};

}
}
}

#endif
