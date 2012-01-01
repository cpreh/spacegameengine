/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/color_format.hpp>
#include <sge/opengl/color_format_type.hpp>
#include <sge/opengl/internal_color_format.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/instantiate_dim.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/opengl/texture/mipmap/parameters.hpp>
#include <fcppt/math/size_type.hpp>


template<
	fcppt::math::size_type Dim
>
sge::opengl::texture::mipmap::parameters<
	Dim
>::parameters(
	texture::binding const &_binding,
	opengl::context::object &_context,
	texture::type const _type,
	opengl::color_format const _format,
	opengl::color_format_type const _format_type,
	opengl::internal_color_format const _internal_format,
	dim const &_size,
	init_function_type const &_init_function
)
:
	binding_(
		_binding
	),
	context_(
		_context
	),
	type_(
		_type
	),
	format_(
		_format
	),
	format_type_(
		_format_type
	),
	internal_format_(
		_internal_format
	),
	size_(
		_size
	),
	init_function_(
		_init_function
	)
{
}

template<
	fcppt::math::size_type Dim
>
sge::opengl::texture::binding const &
sge::opengl::texture::mipmap::parameters<
	Dim
>::binding() const
{
	return binding_;
}

template<
	fcppt::math::size_type Dim
>
sge::opengl::context::object &
sge::opengl::texture::mipmap::parameters<
	Dim
>::context() const
{
	return context_;
}

template<
	fcppt::math::size_type Dim
>
sge::opengl::texture::type const
sge::opengl::texture::mipmap::parameters<
	Dim
>::type() const
{
	return type_;
}

template<
	fcppt::math::size_type Dim
>
sge::opengl::color_format const
sge::opengl::texture::mipmap::parameters<
	Dim
>::format() const
{
	return format_;
}

template<
	fcppt::math::size_type Dim
>
sge::opengl::color_format_type const
sge::opengl::texture::mipmap::parameters<
	Dim
>::format_type() const
{
	return format_type_;
}

template<
	fcppt::math::size_type Dim
>
sge::opengl::internal_color_format const
sge::opengl::texture::mipmap::parameters<
	Dim
>::internal_format() const
{
	return internal_format_;
}

template<
	fcppt::math::size_type Dim
>
typename sge::opengl::texture::mipmap::parameters<
	Dim
>::dim const &
sge::opengl::texture::mipmap::parameters<
	Dim
>::size() const
{
	return size_;
}

template<
	fcppt::math::size_type Dim
>
typename sge::opengl::texture::mipmap::parameters<
	Dim
>::init_function_type const &
sge::opengl::texture::mipmap::parameters<
	Dim
>::init_function() const
{
	return init_function_;
}

#define SGE_OPENGL_TEXTURE_MIPMAP_INSTANTIATE_PARAMETERS(\
	dimension\
)\
template class \
sge::opengl::texture::mipmap::parameters<\
	dimension\
>;

SGE_OPENGL_TEXTURE_INSTANTIATE_DIM(
	SGE_OPENGL_TEXTURE_MIPMAP_INSTANTIATE_PARAMETERS
)
