//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/texture/pp_dims.hpp>
#include <sge/opengl/texture/mipmap/generate_levels.hpp>
#include <sge/opengl/texture/mipmap/parameters.hpp>
#include <sge/renderer/basic_dim.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <sge/renderer/texture/mipmap/level_count.hpp>
#include <fcppt/use.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/dim/at.hpp>
#include <fcppt/math/dim/contents.hpp>
#include <fcppt/math/dim/init.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


namespace
{

template<
	fcppt::math::size_type Size
>
sge::renderer::basic_dim<
	Size
>
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
		_parameters.init_function().get()(
			_parameters.binding(),
			_parameters.config(),
			_parameters.buffer_type(),
			_parameters.format_order(),
			_parameters.format_base_type(),
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
>
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
				auto const _index
			)
			{
				FCPPT_USE(
					_index
				);

				return
					std::max(
						fcppt::math::dim::at<
							_index
						>(
							_size
						)
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
	seq,\
	_,\
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

BOOST_PP_SEQ_FOR_EACH(
	SGE_OPENGL_TEXTURE_MIPMAP_INSTANTIATE_GENERATE_LEVELS,
	_,
	SGE_OPENGL_TEXTURE_PP_DIMS
)
