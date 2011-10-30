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


#ifndef SGE_OPENGL_INDEX_BUFFER_HPP_INCLUDED
#define SGE_OPENGL_INDEX_BUFFER_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/buffer/object.hpp>
#include <sge/opengl/buffer/wrapper.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/renderer/index_buffer.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{

class index_buffer
:
	public sge::renderer::index_buffer,
	public opengl::buffer::wrapper
{
	FCPPT_NONCOPYABLE(
		index_buffer
	);
public:
	index_buffer(
		context::object &,
		renderer::index::dynamic::format::type,
		count_type,
		renderer::resource_flags_field const &
	);

	~index_buffer();

	GLenum
	gl_format() const;

	GLvoid *
	buffer_offset(
		first_type
	) const;

	void
	bind() const;
private:
	view_type const
	lock(
		renderer::lock_mode::type,
		first_type,
		count_type
	);

	const_view_type const
	lock(
		first_type,
		count_type
	) const;

	template<
		typename View
	>
	View const
	do_lock(
		renderer::lock_flags::method::type,
		first_type,
		count_type
	) const;

	void
	unlock() const;

	count_type const
	size() const;

	renderer::resource_flags_field const
	resource_flags() const;

	renderer::index::dynamic::format::type
	format() const;

	opengl::buffer::object const &
	buffer() const;

	renderer::index::dynamic::format::type const format_;

	GLenum const gl_format_;

	mutable opengl::buffer::object buffer_;
};

}
}

#endif

