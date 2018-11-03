/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/color_base_type.hpp>
#include <sge/opengl/color_order.hpp>
#include <sge/opengl/internal_color_format.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/pp_dims.hpp>
#include <sge/opengl/texture/mipmap/parameters.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <fcppt/config/external_end.hpp>


template<
	fcppt::math::size_type Dim
>
sge::opengl::texture::mipmap::parameters<
	Dim
>::parameters(
	sge::opengl::texture::binding const &_binding,
	sge::opengl::texture::buffer_type const _buffer_type,
	config_type const &_config,
	sge::opengl::color_order const _format_order,
	sge::opengl::color_base_type const _format_base_type,
	sge::opengl::internal_color_format const _internal_format,
	dim const &_size,
	init_function_type _init_function
)
:
	binding_(
		_binding
	),
	buffer_type_(
		_buffer_type
	),
	config_(
		_config
	),
	format_order_(
		_format_order
	),
	format_base_type_(
		_format_base_type
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
	return
		binding_;
}

template<
	fcppt::math::size_type Dim
>
sge::opengl::texture::buffer_type
sge::opengl::texture::mipmap::parameters<
	Dim
>::buffer_type() const
{
	return
		buffer_type_;
}

template<
	fcppt::math::size_type Dim
>
typename
sge::opengl::texture::mipmap::parameters<
	Dim
>::config_type const &
sge::opengl::texture::mipmap::parameters<
	Dim
>::config() const
{
	return
		config_;
}

template<
	fcppt::math::size_type Dim
>
sge::opengl::color_order
sge::opengl::texture::mipmap::parameters<
	Dim
>::format_order() const
{
	return
		format_order_;
}

template<
	fcppt::math::size_type Dim
>
sge::opengl::color_base_type
sge::opengl::texture::mipmap::parameters<
	Dim
>::format_base_type() const
{
	return
		format_base_type_;
}

template<
	fcppt::math::size_type Dim
>
sge::opengl::internal_color_format
sge::opengl::texture::mipmap::parameters<
	Dim
>::internal_format() const
{
	return
		internal_format_;
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
	return
		size_;
}

template<
	fcppt::math::size_type Dim
>
typename sge::opengl::texture::mipmap::parameters<
	Dim
>::init_function_type
sge::opengl::texture::mipmap::parameters<
	Dim
>::init_function() const
{
	return
		init_function_;
}

#define SGE_OPENGL_TEXTURE_MIPMAP_INSTANTIATE_PARAMETERS(\
	seq,\
	_,\
	dimension\
)\
template \
class \
sge::opengl::texture::mipmap::parameters<\
	dimension\
>;

BOOST_PP_SEQ_FOR_EACH(
	SGE_OPENGL_TEXTURE_MIPMAP_INSTANTIATE_PARAMETERS,
	_,
	SGE_OPENGL_TEXTURE_PP_DIMS
)
