/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_OPENGL_TEXTURE_BASIC_BUFFER_IMPL_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BASIC_BUFFER_IMPL_HPP_INCLUDED

#include <sge/opengl/texture/basic_buffer.hpp>
#include <sge/opengl/texture/basic_buffer_parameters.hpp>
#include <sge/opengl/texture/buffer_base.hpp>
#include <sge/opengl/texture/get_level_size.hpp>
#include <fcppt/math/dim/object_impl.hpp>


template<
	typename Types
>
sge::opengl::texture::basic_buffer<
	Types
>::basic_buffer(
	format_type const _format,
	sge::opengl::texture::basic_buffer_parameters const &_parameters
)
:
	base_type(),
	sge::opengl::texture::buffer_base(
		_parameters.buffer_type(),
		_parameters.id(),
		_parameters.level(),
		_parameters.is_render_target()
	),
	size_(
		sge::opengl::texture::get_level_size<
			dim::dim_wrapper::value
		>(
			_parameters.binding(),
			_parameters.buffer_type(),
			_parameters.level()
		)
	),
	format_(
		_format
	)
{
}

template<
	typename Types
>
sge::opengl::texture::basic_buffer<
	Types
>::~basic_buffer()
{
}

template<
	typename Types
>
typename
sge::opengl::texture::basic_buffer<
	Types
>::dim
sge::opengl::texture::basic_buffer<
	Types
>::size() const
{
	return
		size_;
}

template<
	typename Types
>
typename
sge::opengl::texture::basic_buffer<
	Types
>::format_type
sge::opengl::texture::basic_buffer<
	Types
>::format() const
{
	return
		format_;
}

#endif
