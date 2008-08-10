/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_PBO_HPP_INCLUDED
#define SGE_OPENGL_PBO_HPP_INCLUDED

#include "common.hpp"
#include "lock_method.hpp"
#include <sge/renderer/resource_flags.hpp>
#include <cstddef>

namespace sge
{
namespace ogl
{

class vbo_base;

class pbo_base {
public:
	typedef std::size_t                                    size_type;
	typedef std::ptrdiff_t                                 difference_type;
	typedef unsigned char                                  value_type;
	typedef value_type                                    *pointer;
	typedef value_type const                              *const_pointer;
	typedef renderer::resource_flag_t                      resource_flag_type;
	typedef lock_method::type                              lock_flag_type;

	static size_type const npos = static_cast<size_type>(-1);

	virtual void do_lock(
		lock_flag_type,
		size_type first = 0,
		size_type count = npos) = 0;
	virtual void do_unlock() = 0;

	virtual size_type size() const = 0;

	virtual pointer data() = 0;
	virtual const_pointer data() const = 0;

	virtual void unbind() const = 0;
	virtual void bind_me() const = 0;

	virtual pointer buffer_offset(size_type) const = 0;

	virtual ~pbo_base();
};

GLenum pixel_pack_buffer_type();
GLenum pixel_unpack_buffer_type();

void initialize_pbo();
vbo_base& pbo_impl();
bool pbo_in_hardware();

}
}

#endif
