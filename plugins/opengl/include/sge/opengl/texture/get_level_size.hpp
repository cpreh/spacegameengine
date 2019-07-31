//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_GET_LEVEL_SIZE_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_GET_LEVEL_SIZE_HPP_INCLUDED

#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/opengl/texture/pp_dims.hpp>
#include <sge/renderer/basic_dim_fwd.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

template<
	fcppt::math::size_type Size
>
sge::renderer::basic_dim<
	Size
>
get_level_size(
	sge::opengl::texture::binding const &,
	sge::opengl::texture::buffer_type,
	sge::renderer::texture::mipmap::level
);

}
}
}

#define SGE_OPENGL_TEXTURE_DECLARE_GET_LEVEL_SIZE(\
	seq,\
	_,\
	dimension\
)\
extern \
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
);

BOOST_PP_SEQ_FOR_EACH(
	SGE_OPENGL_TEXTURE_DECLARE_GET_LEVEL_SIZE,
	_,
	SGE_OPENGL_TEXTURE_PP_DIMS
)

#endif
