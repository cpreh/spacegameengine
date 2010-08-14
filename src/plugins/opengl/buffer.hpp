/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_BUFFER_HPP_INCLUDED
#define SGE_OPENGL_BUFFER_HPP_INCLUDED

#include "buffer_fwd.hpp"
#include "common.hpp"
#include "lock_method.hpp"
#include "vbo_base_fwd.hpp"
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/raw_value.hpp>
#include <fcppt/container/bitfield/basic_decl.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opengl
{

class buffer
{
	FCPPT_NONCOPYABLE(buffer)
public:
	typedef renderer::size_type                  size_type;
	typedef sge::renderer::raw_value             value_type;
	typedef value_type                           *pointer;
	typedef value_type const                     *const_pointer;
	typedef renderer::resource_flags_field       resource_flag_type;
	typedef lock_method::type                    lock_flag_type;

	buffer(
		vbo_base &,
		GLenum type,
		size_type size,
		size_type stride,
		resource_flag_type flags,
		const_pointer src
	);

	~buffer();

	static size_type const npos = static_cast<size_type>(-1);

	void
	lock(
		lock_flag_type lock_flags,
		size_type first = 0,
		size_type count = npos
	);

	void
	unlock();

	void
	sub_data(
		const_pointer data,
		size_type first,
		size_type count
	);

	size_type
	size() const;

	size_type
	stride() const;

	resource_flag_type
	flags() const;

	pointer
	data();

	const_pointer
	data() const;

	size_type
	lock_size() const;

	void
	unbind();

	void
	bind_me() const;

	pointer
	buffer_offset(
		size_type offset
	) const;
private:
	void
	bind(
		GLuint id
	) const;

	void
	check_lock() const;

	vbo_base &vbo_base_;

	GLenum const type_;

	size_type const
		size_,
		stride_;

	resource_flag_type const flags_;

	pointer dest_;

	GLuint const id_;

	size_type
		lock_offset_,
		lock_size_;
};

}
}

#endif
