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


#ifndef SGE_OPENGL_BASIC_BUFFER_IMPL_HPP_INCLUDED
#define SGE_OPENGL_BASIC_BUFFER_IMPL_HPP_INCLUDED

#include "../../exception.hpp"
#include "basic_buffer.hpp"
#include "conversion.hpp"
#include "vbo_base.hpp"

template<typename Base>
sge::ogl::basic_buffer<Base>::basic_buffer(
	const GLenum type,
	vbo_base& impl,
	const size_type sz,
	const size_type stride_,
	const resource_flag_t flags_,
	const const_pointer src)
 : type(type),
   impl(impl),
   sz(sz),
   stride_(stride_),
   flags_(flags_),
   dest(0),
   id(impl.gen_buffer())
{
	set_size(src);
}

template<typename Base>
sge::ogl::basic_buffer<Base>::~basic_buffer()
{
	if(dest)
		unlock();
	unbind();
	impl.delete_buffer(id);
}

template<typename Base>
void sge::ogl::basic_buffer<Base>::lock(const lock_flag_t lockflags)
{
	if(dest)
		throw exception(SGE_TEXT("ogl_buffer::lock(), you have to unlock before locking!"));
		
	const GLuint glflags = convert_cast<GLuint>(lockflags);
	bind_me();
	dest = static_cast<pointer>(impl.map_buffer(type, glflags));
}

template<typename Base>
void sge::ogl::basic_buffer<Base>::unlock()
{
	if(!dest)
		throw exception(SGE_TEXT("ogl_buffer::unlock(), buffer is not locked! cannot unlock!"));
	bind_me();
	impl.unmap_buffer(type);
	dest = 0;
}

template<typename Base>
void sge::ogl::basic_buffer<Base>::set_data(
	const const_pointer data,
	const size_type first,
	const size_type count)
{
	if(first + count > size())
		throw exception(SGE_TEXT("ogl_buffer::set_data(), first + count out of range!"));
	if(dest)
		throw exception(SGE_TEXT("ogl_buffer::set_data(), buffer must not be locked!"));
	bind_me();
	impl.buffer_sub_data(
		type,
		static_cast<GLsizei>(first * stride_),
		static_cast<GLsizei>(count * stride_),
		data);
}

template<typename Base>
typename sge::ogl::basic_buffer<Base>::size_type sge::ogl::basic_buffer<Base>::size() const
{
	return sz;
}

template<typename Base>
sge::resource_flag_t sge::ogl::basic_buffer<Base>::flags() const
{
	return flags_;
}

template<typename Base>
void sge::ogl::basic_buffer<Base>::resize(
	const size_type newsize,
	const const_pointer src)
{
	if(dest)
		throw exception(SGE_TEXT("ogl_buffer::resize(), buffer must be unlocked!"));
	sz = newsize;
	set_size(src);
}

template<typename Base>
typename sge::ogl::basic_buffer<Base>::iterator sge::ogl::basic_buffer<Base>::begin()
{
	return create_iterator(data());
}

template<typename Base>
typename sge::ogl::basic_buffer<Base>::const_iterator sge::ogl::basic_buffer<Base>::begin() const
{
	return create_iterator(data());
}

template<typename Base>
typename sge::ogl::basic_buffer<Base>::pointer sge::ogl::basic_buffer<Base>::data()
{
	check_lock();
	return dest;
}

template<typename Base>
typename sge::ogl::basic_buffer<Base>::const_pointer sge::ogl::basic_buffer<Base>::data() const
{
	check_lock();
	return dest;
}

template<typename Base>
void sge::ogl::basic_buffer<Base>::bind(const GLuint id) const
{
	impl.bind_buffer(type, id);
}

template<typename Base>
void sge::ogl::basic_buffer<Base>::unbind() const
{
	bind(0);
}

template<typename Base>
void sge::ogl::basic_buffer<Base>::bind_me() const
{
	bind(id);
}

template<typename Base>
typename sge::ogl::basic_buffer<Base>::pointer
sge::ogl::basic_buffer<Base>::buffer_offset(const size_type sz) const
{
	return static_cast<pointer>(
		impl.buffer_offset(
			type,
			static_cast<GLsizei>(sz)));
}

template<typename Base>
void sge::ogl::basic_buffer<Base>::check_lock() const
{
	if(!dest)
		throw exception(SGE_TEXT("ogl_buffer used but the buffer has not been locked!"));
}

template<typename Base>
void sge::ogl::basic_buffer<Base>::set_size(const const_pointer src)
{
	const GLuint glflags = convert_resource_flags(flags());
	const size_type nsz = size() * stride_;
	bind_me();
	impl.buffer_data(type, static_cast<GLsizei>(nsz), src, glflags);
}

#endif
