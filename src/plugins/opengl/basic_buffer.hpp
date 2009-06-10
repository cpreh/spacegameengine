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


#ifndef SGE_OPENGL_BASIC_BUFFER_HPP_INCLUDED
#define SGE_OPENGL_BASIC_BUFFER_HPP_INCLUDED

#include "common.hpp"
#include "lock_method.hpp"
#include <sge/renderer/resource_flags.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/raw_value.hpp>
#include <sge/noncopyable.hpp>

namespace sge
{
namespace opengl
{

class vbo_base;

template<
	GLenum (*Type)(),
	vbo_base& (*Impl)(),
	typename T = renderer::raw_value
>
class basic_buffer {
	SGE_NONCOPYABLE(basic_buffer)
public:
	typedef renderer::size_type                  size_type;
	typedef T                                    value_type;
	typedef value_type                           *pointer;
	typedef value_type const                     *const_pointer;
	typedef renderer::resource_flag_t            resource_flag_type;
	typedef lock_method::type                    lock_flag_type;
			
	basic_buffer(
		size_type sz,
		size_type stride,
		resource_flag_type flags,
		const_pointer src);
	~basic_buffer();

	static size_type const npos = static_cast<size_type>(-1);

	void lock(
		lock_flag_type lock_flags,
		size_type first = 0,
		size_type count = npos);
	void unlock();
	void sub_data(
		const_pointer data,
		size_type first,
		size_type count);

	size_type size() const;
	size_type stride() const;
	size_type byte_stride() const;
	resource_flag_type flags() const;

	pointer data();
	const_pointer data() const;
	size_type lock_size() const;

	static void unbind();
	void bind_me() const;
	
	pointer
	buffer_offset(
		size_type offset) const;
private:
	static void bind(GLuint id);
	void check_lock() const;

	size_type          sz,
	                   stride_;
	resource_flag_type flags_;
	pointer            dest;
	GLuint             id;
	size_type          lock_offset,
	                   lock_size_;
};

}
}

#endif
