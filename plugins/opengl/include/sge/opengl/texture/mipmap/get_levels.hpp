//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_MIPMAP_GET_LEVELS_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_MIPMAP_GET_LEVELS_HPP_INCLUDED

#include <sge/opengl/texture/pp_dims.hpp>
#include <sge/renderer/basic_dim_fwd.hpp>
#include <sge/renderer/texture/mipmap/level_count.hpp>
#include <sge/renderer/texture/mipmap/object_fwd.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge::opengl::texture::mipmap
{

template<
	fcppt::math::size_type Size
>
sge::renderer::texture::mipmap::level_count
get_levels(
	sge::renderer::texture::mipmap::object const &,
	sge::renderer::basic_dim<
		Size
	> const &
);

}

#define SGE_OPENGL_TEXTURE_MIPMAP_DECLARE_GET_LEVELS(\
	seq,\
	_,\
	dimension\
)\
extern \
template \
sge::renderer::texture::mipmap::level_count \
sge::opengl::texture::mipmap::get_levels<\
	dimension \
>(\
	sge::renderer::texture::mipmap::object const &,\
	sge::renderer::basic_dim<\
		dimension \
	> const & \
);

BOOST_PP_SEQ_FOR_EACH(
	SGE_OPENGL_TEXTURE_MIPMAP_DECLARE_GET_LEVELS,
	_,
	SGE_OPENGL_TEXTURE_PP_DIMS
)

#endif
