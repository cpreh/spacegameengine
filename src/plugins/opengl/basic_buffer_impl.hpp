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


#ifndef SGE_OGL_BASIC_BUFFER_IMPL_HPP_INCLUDED
#define SGE_OGL_BASIC_BUFFER_IMPL_HPP_INCLUDED

#include "conversion.hpp"
#include "vbo.hpp"

template<typename Base, GLenum Type>
sge::ogl::basic_buffer<Base, Type>::basic_buffer(const size_type sz, const size_type stride_, const resource_flag_t flags_, const const_pointer src)
 : sz(sz),
   stride_(stride_),
   flags_(flags_),
   dest(0)
{
	check_vbo_extension();
	id = gen_buffer();
	set_size(src);
}

template<typename Base, GLenum Type>
sge::ogl::basic_buffer<Base, Type>::~basic_buffer()
{
	delete_buffer(id);
}

template<typename Base, GLenum Type>
void sge::ogl::basic_buffer<Base, Type>::lock(const lock_flag_t lockflags)
{
	if(dest)
		throw exception("ogl_buffer::lock(), you have to unlock before locking!");
		
	const GLuint glflags = convert_lock_flags(lockflags);
	bind_me();
	try
	{
		dest = static_cast<pointer>(map_buffer(Type, glflags));
	}
	catch(const exception&)
	{
		dest = 0;
	}
}

template<typename Base, GLenum Type>
void sge::ogl::basic_buffer<Base, Type>::unlock()
{
	if(!dest)
		throw exception("ogl_buffer::unlock(), buffer is not locked! cannot unlock!");
	bind_me();
	unmap_buffer(Type);
	dest = 0;
}

template<typename Base, GLenum Type>
void sge::ogl::basic_buffer<Base, Type>::set_data(const const_pointer data, const size_type first, const size_type count)
{
	if(first + count > size())
		throw exception("ogl_buffer::set_data(), first + count out of range!");
	if(dest)
		throw exception("ogl_buffer::set_data(), buffer must not be locked!");
	bind_me();
	buffer_sub_data(Type, first * stride_, count * stride_, data);
}

template<typename Base, GLenum Type>
typename sge::ogl::basic_buffer<Base, Type>::iterator sge::ogl::basic_buffer<Base, Type>::end()
{
	return begin() + size();
}
template<typename Base, GLenum Type>
typename sge::ogl::basic_buffer<Base, Type>::const_iterator sge::ogl::basic_buffer<Base, Type>::end() const
{
	return begin() + size();
}

template<typename Base, GLenum Type>
typename sge::ogl::basic_buffer<Base, Type>::reverse_iterator sge::ogl::basic_buffer<Base, Type>::rbegin()
{
	return reverse_iterator(end());
}

template<typename Base, GLenum Type>
typename sge::ogl::basic_buffer<Base, Type>::const_reverse_iterator sge::ogl::basic_buffer<Base, Type>::rbegin() const
{
	return const_reverse_iterator(end());
}

template<typename Base, GLenum Type>
typename sge::ogl::basic_buffer<Base, Type>::reverse_iterator sge::ogl::basic_buffer<Base, Type>::rend()
{
	return reverse_iterator(begin());
}

template<typename Base, GLenum Type>
typename sge::ogl::basic_buffer<Base, Type>::const_reverse_iterator sge::ogl::basic_buffer<Base, Type>::rend() const
{
	return const_reverse_iterator(begin());
}

template<typename Base, GLenum Type>
typename sge::ogl::basic_buffer<Base, Type>::size_type sge::ogl::basic_buffer<Base, Type>::size() const
{
	return sz;
}
template<typename Base, GLenum Type>
sge::resource_flag_t sge::ogl::basic_buffer<Base, Type>::flags() const
{
	return flags_;
}

template<typename Base, GLenum Type>
typename sge::ogl::basic_buffer<Base, Type>::reference sge::ogl::basic_buffer<Base,Type>::operator[](const size_type i)
{
	return *(begin() + i);
}

template<typename Base, GLenum Type>
typename sge::ogl::basic_buffer<Base, Type>::const_reference sge::ogl::basic_buffer<Base,Type>::operator[](const size_type i) const
{
	return *(begin() + i);
}

template<typename Base, GLenum Type>
void sge::ogl::basic_buffer<Base, Type>::resize(const size_type newsize, const const_pointer src)
{
	if(newsize <= size())
		return;
	if(dest)
		throw exception("ogl_buffer::resize(), buffer must be unlocked!");
	sz = newsize;
	set_size(src);
}

template<typename Base, GLenum Type>
typename sge::ogl::basic_buffer<Base, Type>::pointer sge::ogl::basic_buffer<Base, Type>::data()
{
	check_lock();
	return dest;
}

template<typename Base, GLenum Type>
typename sge::ogl::basic_buffer<Base, Type>::const_pointer sge::ogl::basic_buffer<Base, Type>::data() const
{
	check_lock();
	return dest;
}

template<typename Base, GLenum Type>
void sge::ogl::basic_buffer<Base, Type>::bind(const GLuint id)
{
	bind_buffer(Type, id);
}

template<typename Base, GLenum Type>
void sge::ogl::basic_buffer<Base, Type>::unbind()
{
	bind(0);
}

template<typename Base, GLenum Type>
void sge::ogl::basic_buffer<Base, Type>::bind_me() const
{
	bind(id);
}
	
template<typename Base, GLenum Type>
void sge::ogl::basic_buffer<Base, Type>::check_lock() const
{
	if(!dest)
		throw exception("ogl_buffer used but the buffer has not been locked!");
}

template<typename Base, GLenum Type>
void sge::ogl::basic_buffer<Base, Type>::set_size(const const_pointer src)
{
	const GLuint glflags = convert_resource_flags(flags());
	const size_type nsz = size() * stride_;
	bind_me();
	buffer_data(Type, nsz, src, glflags);
}

#endif
