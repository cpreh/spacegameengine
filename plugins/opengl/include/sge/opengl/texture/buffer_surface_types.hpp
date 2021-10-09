//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TEXTURE_BUFFER_SURFACE_TYPES_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BUFFER_SURFACE_TYPES_HPP_INCLUDED

#include <sge/opengl/texture/buffer_surface_types_fwd.hpp>
#include <sge/opengl/texture/init_function.hpp>
#include <sge/opengl/texture/sub_function.hpp>
#include <sge/renderer/size_type.hpp>
#include <fcppt/math/size_type.hpp>

namespace sge::opengl::texture
{

struct buffer_surface_types
{
  [[nodiscard]] static sge::renderer::size_type min_size();

  static constexpr fcppt::math::size_type const num_dims = 2;

  using init_function_type = sge::opengl::texture::init_function<num_dims>;

  [[nodiscard]] static init_function_type init_function();

  using sub_function_type = sge::opengl::texture::sub_function<num_dims>;

  [[nodiscard]] static sub_function_type sub_function();
};

}

#endif
