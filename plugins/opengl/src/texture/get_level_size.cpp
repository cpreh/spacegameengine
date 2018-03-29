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


#include <sge/opengl/common.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/opengl/texture/get_level_size.hpp>
#include <sge/opengl/texture/instantiate_dim.hpp>
#include <sge/opengl/texture/funcs/level_parameter.hpp>
#include <sge/renderer/basic_dim.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/dim3.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/dim/push_back.hpp>


namespace
{

template<
	fcppt::math::size_type Size
>
struct get_level_size_impl;

template<>
struct get_level_size_impl<
	2u
>
{
	static
	sge::renderer::dim2
	execute(
		sge::opengl::texture::binding const &_binding,
		sge::opengl::texture::buffer_type const _buffer_type,
		sge::renderer::texture::mipmap::level const _level
	)
	{
		return
			sge::renderer::dim2(
				fcppt::cast::to_unsigned(
					sge::opengl::texture::funcs::level_parameter(
						_binding,
						_buffer_type,
						_level,
						GL_TEXTURE_WIDTH
					)
				),
				fcppt::cast::to_unsigned(
					sge::opengl::texture::funcs::level_parameter(
						_binding,
						_buffer_type,
						_level,
						GL_TEXTURE_HEIGHT
					)
				)
			);
	}
};

template<>
struct get_level_size_impl<
	3u
>
{
	static
	sge::renderer::dim3
	execute(
		sge::opengl::texture::binding const &_binding,
		sge::opengl::texture::buffer_type const _buffer_type,
		sge::renderer::texture::mipmap::level const _level
	)
	{
		return
			fcppt::math::dim::push_back(
				get_level_size_impl<
					2u
				>::execute(
					_binding,
					_buffer_type,
					_level
				),
				fcppt::cast::size<
					sge::renderer::size_type
				>(
					fcppt::cast::to_unsigned(
						sge::opengl::texture::funcs::level_parameter(
							_binding,
							_buffer_type,
							_level,
							GL_TEXTURE_DEPTH
						)
					)
				)
			);
	}
};

}

template<
	fcppt::math::size_type Size
>
sge::renderer::basic_dim<
	Size
>
sge::opengl::texture::get_level_size(
	sge::opengl::texture::binding const &_binding,
	sge::opengl::texture::buffer_type const _buffer_type,
	sge::renderer::texture::mipmap::level const _level
)
{
	return
		::get_level_size_impl<
			Size
		>::execute(
			_binding,
			_buffer_type,
			_level
		);
}

#define SGE_OPENGL_TEXTURE_INSTANTIATE_GET_LEVEL_SIZE(\
	dimension\
)\
template \
sge::renderer::basic_dim<\
	dimension\
> \
sge::opengl::texture::get_level_size<\
	dimension\
>(\
	sge::opengl::texture::binding const &,\
	sge::opengl::texture::buffer_type,\
	sge::renderer::texture::mipmap::level\
)

SGE_OPENGL_TEXTURE_INSTANTIATE_DIM(
	SGE_OPENGL_TEXTURE_INSTANTIATE_GET_LEVEL_SIZE
);
