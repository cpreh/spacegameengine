//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/texture/pp_dims.hpp>
#include <sge/opengl/texture/mipmap/get_levels.hpp>
#include <sge/renderer/basic_dim.hpp>
#include <sge/renderer/texture/mipmap/all_levels_rep_fwd.hpp>
#include <sge/renderer/texture/mipmap/level_count.hpp>
#include <sge/renderer/texture/mipmap/levels_rep.hpp>
#include <sge/renderer/texture/mipmap/object.hpp>
#include <sge/renderer/texture/mipmap/off_rep_fwd.hpp>
#include <sge/renderer/texture/mipmap/variant.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/log2.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/to_array.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/range/algorithm/max_element.hpp>
#include <fcppt/config/external_end.hpp>


template<
	fcppt::math::size_type Size
>
sge::renderer::texture::mipmap::level_count
sge::opengl::texture::mipmap::get_levels(
	sge::renderer::texture::mipmap::object const &_mipmap,
	sge::renderer::basic_dim<
		Size
	> const &_dim
)
{
	return
		fcppt::variant::match(
			_mipmap.variant(),
			[](
				sge::renderer::texture::mipmap::off_rep const &
			)
			{
				return
					sge::renderer::texture::mipmap::level_count(
						1u
					);
			},
			[
				&_dim
			](
				sge::renderer::texture::mipmap::all_levels_rep const &
			)
			{
				return
					fcppt::strong_typedef_construct_cast<
						sge::renderer::texture::mipmap::level_count,
						fcppt::cast::size_fun
					>(
						1u
						+
						fcppt::math::log2(
							// TODO!
							*boost::range::max_element(
								fcppt::math::to_array(
									_dim
								)
							)
						)
					);
			},
			[](
				sge::renderer::texture::mipmap::levels_rep const &_levels
			)
			{
				return
					_levels.value();
			}
		);
}

#define SGE_OPENGL_TEXTURE_MIPMAP_INSTANTIATE_GET_LEVELS(\
	seq,\
	_,\
	dimension\
)\
template \
sge::renderer::texture::mipmap::level_count \
sge::opengl::texture::mipmap::get_levels<\
	dimension\
>(\
	sge::renderer::texture::mipmap::object const &,\
	sge::renderer::basic_dim<\
		dimension\
	> const &\
);

BOOST_PP_SEQ_FOR_EACH(
	SGE_OPENGL_TEXTURE_MIPMAP_INSTANTIATE_GET_LEVELS,
	_,
	SGE_OPENGL_TEXTURE_PP_DIMS
)
