//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/texture/check_dim.hpp>
#include <sge/opengl/texture/pp_dims.hpp>
#include <sge/opengl/texture/warn_min.hpp>
#include <sge/opengl/texture/warn_pow2.hpp>
#include <sge/renderer/basic_dim.hpp>
#include <sge/renderer/size_type.hpp>
#include <fcppt/string.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <fcppt/config/external_end.hpp>

template <fcppt::math::size_type Size>
void sge::opengl::texture::check_dim(
    fcppt::log::object &_log,
    sge::renderer::basic_dim<Size> const &_dim,
    sge::renderer::size_type const _min_value,
    fcppt::string const &_what)
{
  sge::opengl::texture::warn_min(_log, _dim, _min_value, _what);

  sge::opengl::texture::warn_pow2(_log, _dim, _what);
}

#define SGE_OPENGL_TEXTURE_INSTANTIATE_CHECK_DIM(seq, _, dimension) \
  template void sge::opengl::texture::check_dim<dimension>( \
      fcppt::log::object &, \
      sge::renderer::basic_dim<dimension> const &, \
      sge::renderer::size_type, \
      fcppt::string const &);

BOOST_PP_SEQ_FOR_EACH(SGE_OPENGL_TEXTURE_INSTANTIATE_CHECK_DIM, _, SGE_OPENGL_TEXTURE_PP_DIMS)
