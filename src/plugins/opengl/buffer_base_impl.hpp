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


#ifndef SGE_OPENGL_BUFFER_BASE_IMPL_HPP_INCLUDED
#define SGE_OPENGL_BUFFER_BASE_IMPL_HPP_INCLUDED

#include "buffer_base.hpp"

template<
	typename Base,
	GLenum Type,
	vbo_base &(*Impl)()>
sge::ogl::buffer_base<Base, Type, Impl>::buffer_base(
	size_type const sz,
	size_type const stride,
	resources_flag_type const flags,
	const_pointer const src)
: buf(
	sz,
	stride,
	flags,
	src)
{}

template<
	typename Base,
	GLenum Type,
	vbo_base &(*Impl)()>
typename sge::ogl::buffer_base<Base, Type, Impl>::pointer
sge::ogl::buffer_base<Base, Type, Impl>::data()
{
	return buf.data();
}

template<
	typename Base,
	GLenum Type,
	vbo_base &(*Impl)()>
typename sge::ogl::buffer_base<Base, Type, Impl>::const_pointer
sge::ogl::buffer_base<Base, Type, Impl>::data() const
{
	return buf.data();
}

template<
	typename Base,
	GLenum Type,
	vbo_base &(*Impl)()>
typename sge::ogl::buffer_base<Base, Type, Impl>::size_type
sge::ogl::buffer_base<Base, Type, Impl>::lock_size() const
{
	return buf.lock_size();
}

template<
	typename Base,
	GLenum Type,
	vbo_base &(*Impl)()>
typename sge::ogl::buffer_base<Base, Type, Impl>::view_type const
sge::ogl::buffer_base<Base, Type, Impl>::lock(
	lock_flag_type const flags,
	size_type const first,
	size_type const count)
{
	buf.lock(
		convert_lock_method(flags),
		first,
		count);
	return view();
}

template<
	typename Base,
	GLenum Type,
	vbo_base &(*Impl)()>
typename sge::ogl::buffer_base<Base, Type, Impl>::const_view_type const
sge::ogl::buffer_base<Base, Type, Impl>::lock(
	size_type const first,
	size_type const count) const
{
	buf.lock(
		lock_method::readonly,
		first,
		count);
	return view();
}

template<
	typename Base,
	GLenum Type,
	vbo_base &(*Impl)()>
void sge::ogl::buffer_base<Base, Type, Impl>::unlock() const
{
	buf.unlock();
}

template<
	typename Base,
	GLenum Type,
	vbo_base &(*Impl)()>
typename sge::ogl::buffer_base<Base, Type, Impl>::size_type
sge::ogl::buffer_base<Base, Type, Impl>::size() const
{
	return buf.size();
}

template<
	typename Base,
	GLenum Type,
	vbo_base &(*Impl)()>
typename sge::ogl::buffer_base<Base, Type, Impl>::size_type
sge::ogl::buffer_base<Base, Type, Impl>::stride() const
{
	return buf.stride();
}

template<
	typename Base,
	GLenum Type,
	vbo_base &(*Impl)()>
typename sge::ogl::buffer_base<Base, Type, Impl>::resource_flag_type
sge::ogl::buffer_base<Base, Type, Impl>::flags() const
{
	return buf.flags();
}

#endif
