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

#include "basic_buffer.hpp"
#include "conversion.hpp"
#include "common.hpp"
#include "vbo_base.hpp"
#include <sge/exception.hpp>

template<
	typename Base,
	GLenum (*Type)(),
	sge::ogl::vbo_base& (*Impl)()>
sge::ogl::basic_buffer<Base, Type, Impl>::basic_buffer(
	const size_type sz,
	const size_type stride_,
	const resource_flag_type flags_,
	const const_pointer src)
 : sz(sz),
   stride_(stride_),
   flags_(flags_),
   dest(0),
   id(Impl().gen_buffer())
{
	set_size(src);
}

template<
	typename Base,
	GLenum (*Type)(),
	sge::ogl::vbo_base& (*Impl)()>
sge::ogl::basic_buffer<Base, Type, Impl>::~basic_buffer()
{
	if(dest)
		unlock();
	unbind();
	Impl().delete_buffer(id);
}

template<
	typename Base,
	GLenum (*Type)(),
	sge::ogl::vbo_base& (*Impl)()>
void sge::ogl::basic_buffer<Base, Type, Impl>::lock(
	const lock_flag_type lockflags)
{
	if(dest)
		throw exception(SGE_TEXT("ogl_buffer::lock(), you have to unlock before locking!"));
		
	const GLuint glflags = convert_cast(lockflags);
	bind_me();
	dest = static_cast<pointer>(Impl().map_buffer(Type(), glflags));
}

template<
	typename Base,
	GLenum (*Type)(),
	sge::ogl::vbo_base& (*Impl)()>
void sge::ogl::basic_buffer<Base, Type, Impl>::unlock()
{
	if(!dest)
		throw exception(SGE_TEXT("ogl_buffer::unlock(), buffer is not locked! cannot unlock!"));
	bind_me();
	Impl().unmap_buffer(Type());
	dest = 0;
}

template<
	typename Base,
	GLenum (*Type)(),
	sge::ogl::vbo_base& (*Impl)()>
void sge::ogl::basic_buffer<Base, Type, Impl>::sub_data(
	const const_pointer data,
	const size_type first,
	const size_type count)
{
	if(first + count > size())
		throw exception(SGE_TEXT("ogl_buffer::sub_data(), first + count out of range!"));
	if(dest)
		throw exception(SGE_TEXT("ogl_buffer::sub_data(), buffer must not be locked!"));
	bind_me();
	Impl().buffer_sub_data(
		Type(),
		static_cast<GLsizei>(first * stride_),
		static_cast<GLsizei>(count * stride_),
		data);
}

template<
	typename Base,
	GLenum (*Type)(),
	sge::ogl::vbo_base& (*Impl)()>
typename sge::ogl::basic_buffer<Base, Type, Impl>::size_type
sge::ogl::basic_buffer<Base, Type, Impl>::size() const
{
	return sz;
}

template<
	typename Base,
	GLenum (*Type)(),
	sge::ogl::vbo_base& (*Impl)()>
typename sge::ogl::basic_buffer<Base, Type, Impl>::resource_flag_type
sge::ogl::basic_buffer<Base, Type, Impl>::flags() const
{
	return flags_;
}

template<
	typename Base,
	GLenum (*Type)(),
	sge::ogl::vbo_base& (*Impl)()>
void sge::ogl::basic_buffer<Base, Type, Impl>::resize(
	const size_type newsize,
	const size_type newstride,
	const const_pointer src)
{
	if(dest)
		throw exception(SGE_TEXT("ogl_buffer::resize(), buffer must be unlocked!"));
	stride_ = newstride;
	sz = newsize;
	set_size(src);
}

template<
	typename Base,
	GLenum (*Type)(),
	sge::ogl::vbo_base& (*Impl)()>
typename sge::ogl::basic_buffer<Base, Type, Impl>::pointer
sge::ogl::basic_buffer<Base, Type, Impl>::data()
{
	check_lock();
	return dest;
}

template<
	typename Base,
	GLenum (*Type)(),
	sge::ogl::vbo_base& (*Impl)()>
typename sge::ogl::basic_buffer<Base, Type, Impl>::const_pointer
sge::ogl::basic_buffer<Base, Type, Impl>::data() const
{
	return const_cast<const_pointer>(
		const_cast<basic_buffer&>(*this).data());
}

template<
	typename Base,
	GLenum (*Type)(),
	sge::ogl::vbo_base& (*Impl)()>
void sge::ogl::basic_buffer<Base, Type, Impl>::bind(
	const GLuint id) const
{
	Impl().bind_buffer(Type(), id);
}

template<
	typename Base,
	GLenum (*Type)(),
	sge::ogl::vbo_base& (*Impl)()>
void sge::ogl::basic_buffer<Base, Type, Impl>::unbind() const
{
	bind(0);
}

template<
	typename Base,
	GLenum (*Type)(),
	sge::ogl::vbo_base& (*Impl)()>
void sge::ogl::basic_buffer<Base, Type, Impl>::bind_me() const
{
	bind(id);
}

template<
	typename Base,
	GLenum (*Type)(),
	sge::ogl::vbo_base& (*Impl)()>
typename sge::ogl::basic_buffer<Base, Type, Impl>::pointer
sge::ogl::basic_buffer<Base, Type, Impl>::buffer_offset(
	const size_type sz) const
{
	return static_cast<pointer>(
		Impl().buffer_offset(
			Type(),
			static_cast<GLsizei>(sz)));
}

template<
	typename Base,
	GLenum (*Type)(),
	sge::ogl::vbo_base& (*Impl)()>
void sge::ogl::basic_buffer<Base, Type, Impl>::check_lock() const
{
	if(!dest)
		throw exception(SGE_TEXT("ogl_buffer used but the buffer has not been locked!"));
}

template<
	typename Base,
	GLenum (*Type)(),
	sge::ogl::vbo_base& (*Impl)()>
void sge::ogl::basic_buffer<Base, Type, Impl>::set_size(
	const const_pointer src)
{
	const GLuint glflags = convert_resource_flags(flags());
	const size_type nsz = size() * stride_;
	bind_me();
	Impl().buffer_data(Type(), static_cast<GLsizei>(nsz), src, glflags);
}

#endif
