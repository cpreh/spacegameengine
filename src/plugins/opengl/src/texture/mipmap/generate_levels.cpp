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


#include <sge/opengl/texture/instantiate_dim.hpp>
#include <sge/opengl/texture/mipmap/generate_levels.hpp>
#include <sge/opengl/texture/mipmap/parameters.hpp>
#include <sge/renderer/basic_dim.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <sge/renderer/texture/mipmap/level_count.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/dim/contents.hpp>
#include <fcppt/math/dim/init.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


namespace
{

template<
	fcppt::math::size_type Size
>
sge::renderer::basic_dim<
	Size
> const
reduce_dim(
	sge::renderer::basic_dim<
		Size
	> const &
);

}

template<
	fcppt::math::size_type Size
>
void
sge::opengl::texture::mipmap::generate_levels(
	sge::opengl::texture::mipmap::parameters<
		Size
	> const &_parameters,
	sge::renderer::texture::mipmap::level_count const _levels
)
{
	typedef typename sge::opengl::texture::mipmap::parameters<
		Size
	>::dim dim;

	sge::renderer::texture::mipmap::level level(
		1u
	);

	for(
		dim size(
			::reduce_dim<
				Size
			>(
				_parameters.size()
			)
		)
		;
		fcppt::math::dim::contents(
			size
		)
		!= 1u
		&&
		level.get() <= _levels.get()
		;
		size =
			::reduce_dim<
				Size
			>(
				size
			)
		,
		++level
	)
		_parameters.init_function()(
			_parameters.binding(),
			_parameters.system_context(),
			_parameters.buffer_type(),
			_parameters.format(),
			_parameters.format_type(),
			_parameters.internal_format(),
			level,
			size,
			nullptr
		);
}

namespace
{

template<
	fcppt::math::size_type Size
>
sge::renderer::basic_dim<
	Size
> const
reduce_dim(
	sge::renderer::basic_dim<
		Size
	> const &_size
)
{
	typedef
	sge::renderer::basic_dim<
		Size
	>
	dim;

	return
		fcppt::math::dim::init<
			dim
		>(
			[
				&_size
			](
				typename dim::size_type const _index
			)
			{
				return
					std::max(
						_size[
							_index
						]
						/
						fcppt::literal<
							typename
							dim::value_type
						>(
							2
						),
						fcppt::literal<
							typename
							dim::value_type
						>(
							1u
						)
					);
			}
		);
}

}


#define SGE_OPENGL_TEXTURE_MIPMAP_INSTANTIATE_GENERATE_LEVELS(\
	dimension\
)\
template \
void \
sge::opengl::texture::mipmap::generate_levels<\
	dimension\
>(\
	sge::opengl::texture::mipmap::parameters<\
		dimension\
	> const &,\
	sge::renderer::texture::mipmap::level_count\
)

SGE_OPENGL_TEXTURE_INSTANTIATE_DIM(
	SGE_OPENGL_TEXTURE_MIPMAP_INSTANTIATE_GENERATE_LEVELS
);
