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


#ifndef SGE_OPENGL_BASIC_BUFFER_IMPL_HPP_INCLUDED
#define SGE_OPENGL_BASIC_BUFFER_IMPL_HPP_INCLUDED

#include "basic_buffer.hpp"
#include "common.hpp"
#include "vbo_base.hpp"
#include "lock_method.hpp"
#include "convert_resource_flags.hpp"
#include <sge/container/bitfield/basic_impl.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>

template<
	GLenum (*Type)(),
	sge::opengl::vbo_base &(*Impl)(),
	typename T
>
sge::opengl::basic_buffer<Type, Impl, T>::basic_buffer(
	size_type const sz,
	size_type const stride_,
	resource_flag_type const flags_,
	const_pointer const src)
:
	sz(sz),
	stride_(stride_),
	flags_(flags_),
	dest(0),
	id(Impl().gen_buffer()),
	lock_offset(0),
	lock_size_(0)
{
	GLuint const glflags = convert_resource_flags(flags());
	size_type const nsz = size() * byte_stride();

	if(nsz == 0)
		throw exception(
			SGE_TEXT("ogl_buffer: cannot create an empty buffer!"));

	bind_me();

	Impl().buffer_data(
		Type(),
		static_cast<GLsizei>(nsz),
		src,
		glflags
	);
}

template<
	GLenum (*Type)(),
	sge::opengl::vbo_base &(*Impl)(),
	typename T
>
sge::opengl::basic_buffer<Type, Impl, T>::~basic_buffer()
{
	if(dest)
		unlock();
	unbind();
	Impl().delete_buffer(id);
}

template<
	GLenum (*Type)(),
	sge::opengl::vbo_base &(*Impl)(),
	typename T
>
void sge::opengl::basic_buffer<Type, Impl, T>::lock(
	lock_flag_type const lockflags,
	size_type const first,
	size_type count)
{
	if(dest)
		throw exception(
			SGE_TEXT("ogl_buffer::lock(): you have to unlock before locking!"));

	if(lock_flag_read(lockflags) && !(flags() & renderer::resource_flags::readable))
		throw exception(
			SGE_TEXT("ogl_buffer: Cannot lock a writeonly buffer for reading!"));

	if(first > size())
		throw exception(
			SGE_TEXT("ogl_buffer::lock(): first out of range!"));

	if(count == npos)
		count = size() - first;

	if(first + count > size())
		throw exception(
			SGE_TEXT("ogl_buffer::lock(): first + count > size()"));

	GLuint const glflags = ogl_lock_method(lockflags);
	bind_me();
	dest = static_cast<pointer>(Impl().map_buffer(Type(), glflags));
	lock_offset = first * stride();
	lock_size_ = count * stride();
}

template<
	GLenum (*Type)(),
	sge::opengl::vbo_base &(*Impl)(),
	typename T
>
void sge::opengl::basic_buffer<Type, Impl, T>::unlock()
{
	if(!dest)
		throw exception(
			SGE_TEXT("ogl_buffer::unlock(), buffer is not locked! cannot unlock!"));
	bind_me();
	Impl().unmap_buffer(Type());
	dest = 0;
	lock_offset = lock_size_ = 0;
}


template<
	GLenum (*Type)(),
	sge::opengl::vbo_base &(*Impl)(),
	typename T
>
void sge::opengl::basic_buffer<Type, Impl, T>::sub_data(
	const_pointer const data,
	size_type const first,
	size_type const count)
{
	if(first + count > size())
		throw exception(SGE_TEXT("ogl_buffer::sub_data(), first + count out of range!"));
	if(dest)
		throw exception(SGE_TEXT("ogl_buffer::sub_data(), buffer must not be locked!"));
	bind_me();
	Impl().buffer_sub_data(
		Type(),
		static_cast<GLsizei>(first * byte_stride()),
		static_cast<GLsizei>(count * byte_stride()),
		data);
}

template<
	GLenum (*Type)(),
	sge::opengl::vbo_base& (*Impl)(),
	typename T
>
typename sge::opengl::basic_buffer<Type, Impl, T>::size_type
sge::opengl::basic_buffer<Type, Impl, T>::size() const
{
	return sz;
}

template<
	GLenum (*Type)(),
	sge::opengl::vbo_base &(*Impl)(),
	typename T
>
typename sge::opengl::basic_buffer<Type, Impl, T>::size_type
sge::opengl::basic_buffer<Type, Impl, T>::stride() const
{
	return stride_;
}

template<
	GLenum (*Type)(),
	sge::opengl::vbo_base &(*Impl)(),
	typename T
>
typename sge::opengl::basic_buffer<Type, Impl, T>::size_type
sge::opengl::basic_buffer<Type, Impl, T>::byte_stride() const
{
	return stride() * sizeof(value_type);
}

template<
	GLenum (*Type)(),
	sge::opengl::vbo_base &(*Impl)(),
	typename T
>
typename sge::opengl::basic_buffer<Type, Impl, T>::resource_flag_type
sge::opengl::basic_buffer<Type, Impl, T>::flags() const
{
	return flags_;
}

template<
	GLenum (*Type)(),
	sge::opengl::vbo_base &(*Impl)(),
	typename T
>
typename sge::opengl::basic_buffer<Type, Impl, T>::pointer
sge::opengl::basic_buffer<Type, Impl, T>::data()
{
	check_lock();
	return dest + lock_offset;
}

template<
	GLenum (*Type)(),
	sge::opengl::vbo_base &(*Impl)(),
	typename T
>
typename sge::opengl::basic_buffer<Type, Impl, T>::const_pointer
sge::opengl::basic_buffer<Type, Impl, T>::data() const
{
	return const_cast<const_pointer>(
		const_cast<basic_buffer &>(*this).data());
}

template<
	GLenum (*Type)(),
	sge::opengl::vbo_base &(*Impl)(),
	typename T
>
typename sge::opengl::basic_buffer<Type, Impl, T>::size_type
sge::opengl::basic_buffer<Type, Impl, T>::lock_size() const
{
	return lock_size_;
}

template<
	GLenum (*Type)(),
	sge::opengl::vbo_base &(*Impl)(),
	typename T
>
void sge::opengl::basic_buffer<Type, Impl, T>::bind(
	GLuint const id)
{
	Impl().bind_buffer(Type(), id);
}

template<
	GLenum (*Type)(),
	sge::opengl::vbo_base &(*Impl)(),
	typename T
>
void sge::opengl::basic_buffer<Type, Impl, T>::unbind()
{
	bind(0);
}

template<
	GLenum (*Type)(),
	sge::opengl::vbo_base &(*Impl)(),
	typename T
>
void sge::opengl::basic_buffer<Type, Impl, T>::bind_me() const
{
	bind(id);
}

template<
	GLenum (*Type)(),
	sge::opengl::vbo_base &(*Impl)(),
	typename T
>
typename sge::opengl::basic_buffer<Type, Impl, T>::pointer
sge::opengl::basic_buffer<Type, Impl, T>::buffer_offset(
	size_type const sz) const
{
	bind_me();

	return static_cast<pointer>(
		Impl().buffer_offset(
			Type(),
			static_cast<GLsizei>(
				sz * byte_stride())));
}

template<
	GLenum (*Type)(),
	sge::opengl::vbo_base &(*Impl)(),
	typename T
>
void sge::opengl::basic_buffer<Type, Impl, T>::check_lock() const
{
	if(!dest)
		throw exception(
			SGE_TEXT("ogl_buffer used but the buffer has not been locked!"));
}

#endif
