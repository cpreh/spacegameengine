//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/common.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/opengl/texture/get_level_size.hpp>
#include <sge/opengl/texture/pp_dims.hpp>
#include <sge/opengl/texture/funcs/level_parameter.hpp>
#include <sge/renderer/basic_dim.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/dim3.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/dim/push_back.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <fcppt/config/external_end.hpp>

namespace
{

template <fcppt::math::size_type Size>
struct get_level_size_impl;

template <>
struct get_level_size_impl<2U>
{
  static sge::renderer::dim2 execute(
      sge::opengl::texture::binding const &_binding,
      sge::opengl::texture::buffer_type const _buffer_type,
      sge::renderer::texture::mipmap::level const _level)
  {
    return sge::renderer::dim2(
        fcppt::cast::to_unsigned(sge::opengl::texture::funcs::level_parameter(
            _binding, _buffer_type, _level, GL_TEXTURE_WIDTH)),
        fcppt::cast::to_unsigned(sge::opengl::texture::funcs::level_parameter(
            _binding, _buffer_type, _level, GL_TEXTURE_HEIGHT)));
  }
};

template <>
struct get_level_size_impl<3U>
{
  static sge::renderer::dim3 execute(
      sge::opengl::texture::binding const &_binding,
      sge::opengl::texture::buffer_type const _buffer_type,
      sge::renderer::texture::mipmap::level const _level)
  {
    return fcppt::math::dim::push_back(
        get_level_size_impl<2U>::execute(_binding, _buffer_type, _level),
        fcppt::cast::size<sge::renderer::size_type>(
            fcppt::cast::to_unsigned(sge::opengl::texture::funcs::level_parameter(
                _binding, _buffer_type, _level, GL_TEXTURE_DEPTH))));
  }
};

}

template <fcppt::math::size_type Size>
sge::renderer::basic_dim<Size> sge::opengl::texture::get_level_size(
    sge::opengl::texture::binding const &_binding,
    sge::opengl::texture::buffer_type const _buffer_type,
    sge::renderer::texture::mipmap::level const _level)
{
  return ::get_level_size_impl<Size>::execute(_binding, _buffer_type, _level);
}

#define SGE_OPENGL_TEXTURE_INSTANTIATE_GET_LEVEL_SIZE(seq, _, dimension) \
  template sge::renderer::basic_dim<dimension> sge::opengl::texture::get_level_size<dimension>( \
      sge::opengl::texture::binding const &, \
      sge::opengl::texture::buffer_type, \
      sge::renderer::texture::mipmap::level);

BOOST_PP_SEQ_FOR_EACH(SGE_OPENGL_TEXTURE_INSTANTIATE_GET_LEVEL_SIZE, _, SGE_OPENGL_TEXTURE_PP_DIMS)
