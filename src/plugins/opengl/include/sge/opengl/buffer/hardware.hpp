/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/opengl/buffer/hardware_config_fwd.hpp>
#include <sge/opengl/buffer/id.hpp>
#include <sge/opengl/buffer/optional_id.hpp>
#include <sge/opengl/buffer/type.hpp>
#include <fcppt/noncopyable.hpp>


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
	hardware(
		sge::opengl::buffer::type,
		sge::opengl::buffer::hardware_config const &
	);

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
		sge::opengl::buffer::optional_id const &
	)
	override;

	GLvoid *
	map_buffer(
		GLenum flags
	)
	override;

	GLvoid *
	map_buffer_range(
		GLenum flags,
		GLsizei first,
		GLsizei size
	)
	override;

	bool
	map_buffer_range_supported() const
	override;

	void
	unmap_buffer()
	override;

	void
	buffer_data(
		GLsizei size,
		GLvoid const *data,
		GLenum flags
	)
	override;

	void
	buffer_sub_data(
		GLsizei first,
		GLsizei size,
		GLvoid const *data
	)
	override;

	void *
	buffer_offset(
		GLsizei offset
	) const
	override;

	bool
	native() const
	override;

	sge::opengl::buffer::type const type_;

	sge::opengl::buffer::hardware_config const &config_;

	sge::opengl::buffer::optional_id bound_buffer_;
};

}
}
}

#endif
