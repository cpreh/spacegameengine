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


#ifndef SGE_OPENGL_BUFFER_VBO_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_BUFFER_VBO_CONTEXT_HPP_INCLUDED

#include <sge/opengl/buffer/base_fwd.hpp>
#include <sge/opengl/buffer/base_unique_ptr.hpp>
#include <sge/opengl/context/system/base.hpp>
#include <sge/opengl/context/system/id.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace buffer
{

class vbo_context
:
	public sge::opengl::context::system::base
{
	FCPPT_NONCOPYABLE(
		vbo_context
	);
public:
	typedef
	sge::opengl::context::system::object &
	parameter;

	explicit
	vbo_context(
		parameter
	);

	~vbo_context()
	override;

	sge::opengl::buffer::base &
	index_buffer() const;

	sge::opengl::buffer::base &
	vertex_buffer() const;

	static sge::opengl::context::system::id const static_id;
private:
	typedef
	std::array<
		sge::opengl::buffer::base_unique_ptr,
		2u
	>
	buffer_array;

	buffer_array const buffers_;
};

}
}
}

#endif
