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


#ifndef SGE_OPENGL_BUFFER_BASE_HPP_INCLUDED
#define SGE_OPENGL_BUFFER_BASE_HPP_INCLUDED

#include "basic_buffer.hpp"
#include "common.hpp"

namespace sge
{
namespace ogl
{

class vbo_base;

template<
	typename Base,
	GLenum (*Type)(),
	vbo_base &(*Impl)()>
class buffer_base : public Base {
	typedef basic_buffer<
		Type,
		Impl
	> buffer_type;
protected:
	typedef typename Base::size_type              size_type;
	typedef typename buffer_type::pointer         pointer;
	typedef typename buffer_type::const_pointer   const_pointer;
	typedef typename Base::resource_flag_type     resource_flag_type;
	typedef typename Base::lock_flag_type         lock_flag_type;
	typedef typename Base::view_type              view_type;
	typedef typename Base::const_view_type        const_view_type;

	buffer_base(
		size_type sz,
		size_type stride,
		resource_flag_type flags,
		const_pointer src);
	
	pointer data();
	const_pointer data() const;
	size_type lock_size() const;
	size_type stride() const;
	void bind_me() const;
	const_pointer buffer_offset(
		size_type) const;
private:
	view_type const lock(
		lock_flag_type flags,
		size_type first,
		size_type count);
	
	const_view_type const lock(
		size_type first,
		size_type count) const;
	
	void unlock() const;
	
	size_type size() const;
	resource_flag_type flags() const;

	virtual view_type const view() = 0;
	virtual const_view_type const view() const = 0;

	mutable buffer_type buf;
};

}
}

#endif
