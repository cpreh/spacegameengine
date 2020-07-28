//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_CHECK_DIM_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_CHECK_DIM_HPP_INCLUDED

#include <sge/opengl/texture/pp_dims.hpp>
#include <sge/renderer/basic_dim_fwd.hpp>
#include <sge/renderer/size_type.hpp>
#include <fcppt/string.hpp>
#include <fcppt/log/object_fwd.hpp>
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
void
check_dim(
	fcppt::log::object &, // NOLINT(google-runtime-references)
	sge::renderer::basic_dim<
		Size
	> const &,
	sge::renderer::size_type min_value,
	fcppt::string const &what
);

}
}
}

#define SGE_OPENGL_TEXTURE_DECLARE_CHECK_DIM(\
	seq,\
	_,\
	dimension\
)\
extern \
template \
void \
sge::opengl::texture::check_dim<\
	dimension\
>(\
	fcppt::log::object &,\
	sge::renderer::basic_dim< \
		dimension \
	> const &, \
	sge::renderer::size_type, \
	fcppt::string const & \
);

BOOST_PP_SEQ_FOR_EACH(
	SGE_OPENGL_TEXTURE_DECLARE_CHECK_DIM,
	_,
	SGE_OPENGL_TEXTURE_PP_DIMS
)

#endif
