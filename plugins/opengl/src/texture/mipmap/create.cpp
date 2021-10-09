//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/texture/pp_dims.hpp>
#include <sge/opengl/texture/mipmap/all_levels.hpp>
#include <sge/opengl/texture/mipmap/create.hpp>
#include <sge/opengl/texture/mipmap/levels.hpp>
#include <sge/renderer/texture/mipmap/object.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <fcppt/config/external_end.hpp>

template <fcppt::math::size_type Dim>
void sge::opengl::texture::mipmap::create(
    fcppt::log::object &_log,
    sge::opengl::context::object &_context,
    sge::opengl::texture::mipmap::parameters<Dim> const &_parameters,
    sge::renderer::texture::mipmap::object const &_mipmap)
{
  fcppt::variant::match(
      _mipmap.variant(),
      [](sge::renderer::texture::mipmap::off_rep const &) {},
      [&_log, &_context, &_parameters](
          sge::renderer::texture::mipmap::all_levels_rep const &_all_levels)
      { sge::opengl::texture::mipmap::all_levels(_log, _context, _parameters, _all_levels); },
      [&_log, &_context, &_parameters](sge::renderer::texture::mipmap::levels_rep const &_levels)
      { sge::opengl::texture::mipmap::levels(_log, _context, _parameters, _levels); });
}

#define SGE_OPENGL_TEXTURE_MIPMAP_INSTANTIATE_CREATE(seq, _, dimension) \
  template void sge::opengl::texture::mipmap::create<dimension>( \
      fcppt::log::object &, \
      sge::opengl::context::object &, \
      sge::opengl::texture::mipmap::parameters<dimension> const &, \
      sge::renderer::texture::mipmap::object const &);

BOOST_PP_SEQ_FOR_EACH(SGE_OPENGL_TEXTURE_MIPMAP_INSTANTIATE_CREATE, _, SGE_OPENGL_TEXTURE_PP_DIMS)
