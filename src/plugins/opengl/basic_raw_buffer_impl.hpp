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


#ifndef SGE_OPENGL_BASIC_RAW_BUFFER_IMPL_HPP_INCLUDED
#define SGE_OPENGL_BASIC_RAW_BUFFER_IMPL_HPP_INCLUDED

#include "basic_raw_buffer.hpp"

template<typename Base, GLenum (*Type)(), sge::ogl::vbo_base& (*Impl)()>
sge::ogl::basic_raw_buffer<Base, Type, Impl>::basic_raw_buffer(
	const size_type sz,
	const resource_flag_type flags,
	const const_pointer src)
:	base_type(
		Type(),
		Impl(),
		sz,
		sizeof(value_type),
		flags,
		src)
{}

template<typename Base, GLenum (*Type)(), sge::ogl::vbo_base& (*Impl)()>
typename sge::ogl::basic_raw_buffer<Base, Type, Impl>::iterator
sge::ogl::basic_raw_buffer<Base, Type, Impl>::create_iterator(const pointer src)
{
	return iterator(src);
}

template<typename Base, GLenum (*Type)(), sge::ogl::vbo_base& (*Impl)()>
typename sge::ogl::basic_raw_buffer<Base, Type, Impl>::const_iterator
sge::ogl::basic_raw_buffer<Base, Type, Impl>::create_iterator(const const_pointer src) const
{
	return iterator(src);
}

#endif
