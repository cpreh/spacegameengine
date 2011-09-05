/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../generate_levels.hpp"
#include "../parameters.hpp"
#include "../../instantiate_dim.hpp"
#include <sge/renderer/basic_dim.hpp>
#include <sge/renderer/stage.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>

namespace
{

template<
	fcppt::math::size_type Size
>
typename sge::renderer::basic_dim<
	Size
>::type const
reduce_dim(
	typename sge::renderer::basic_dim<
		Size
	>::type const &
);

}

template<
	fcppt::math::size_type Size
>
void
sge::opengl::texture::mipmap::generate_levels(
	mipmap::parameters<
		Size
	> const &_parameters,
	renderer::texture::mipmap::level_count const _levels
)
{
	typedef typename mipmap::parameters<
		Size
	>::dim dim;

	renderer::stage stage(
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
		size.content() != 1
		&& stage.get() <= _levels.get()
		;
		size =
			::reduce_dim<
				Size
			>(
				size
			)
		,
		++stage
	)
		_parameters.init_function()(
			_parameters.scoped_work(),
			_parameters.context(),
			_parameters.type(),
			_parameters.format(),
			_parameters.format_type(),
			_parameters.internal_format(),
			stage,
			size,
			0
		);
}

namespace
{

template<
	fcppt::math::size_type Size
>
typename sge::renderer::basic_dim<
	Size
>::type const
reduce_dim(
	typename sge::renderer::basic_dim<
		Size
	>::type const &_size
)
{
	typedef typename sge::renderer::basic_dim<
		Size
	>::type dim;

	dim ret;

	for(
		typename dim::size_type index(
			0u
		);
		index < _size.size();
		++index
	)
		ret[
			index
		]
			=
			std::max(
				_size[index] / 2,
				static_cast<
					typename dim::value_type
				>(
					1u
				)
			);

	return ret;
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
);

SGE_OPENGL_TEXTURE_INSTANTIATE_DIM(
	SGE_OPENGL_TEXTURE_MIPMAP_INSTANTIATE_GENERATE_LEVELS
)
