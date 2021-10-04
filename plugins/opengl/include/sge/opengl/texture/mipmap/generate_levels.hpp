//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_MIPMAP_GENERATE_LEVELS_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_MIPMAP_GENERATE_LEVELS_HPP_INCLUDED

#include <sge/opengl/texture/pp_dims.hpp>
#include <sge/opengl/texture/mipmap/parameters_fwd.hpp>
#include <sge/renderer/texture/mipmap/level_count.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge::opengl::texture::mipmap
{

template<
	fcppt::math::size_type Size
>
void
generate_levels(
	sge::opengl::texture::mipmap::parameters<
		Size
	> const &,
	sge::renderer::texture::mipmap::level_count
);

}

#define SGE_OPENGL_TEXTURE_MIPMAP_DECLARE_GENERATE_LEVELS(\
	seq,\
	_,\
	dimension\
)\
extern \
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
	SGE_OPENGL_TEXTURE_MIPMAP_DECLARE_GENERATE_LEVELS,
	_,
	SGE_OPENGL_TEXTURE_PP_DIMS
)

#endif
