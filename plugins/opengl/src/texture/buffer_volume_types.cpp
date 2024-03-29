//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/texture/buffer_volume_types.hpp>
#include <sge/opengl/texture/funcs/set_3d.hpp>
#include <sge/opengl/texture/funcs/set_box.hpp>
#include <sge/renderer/size_type.hpp>
#include <fcppt/make_ref.hpp>

sge::renderer::size_type sge::opengl::texture::buffer_volume_types::min_size()
{
  return 16U; // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
}

sge::opengl::texture::buffer_volume_types::init_function_type
sge::opengl::texture::buffer_volume_types::init_function()
{
  return fcppt::make_ref(sge::opengl::texture::funcs::set_3d);
}

sge::opengl::texture::buffer_volume_types::sub_function_type
sge::opengl::texture::buffer_volume_types::sub_function()
{
  return fcppt::make_ref(sge::opengl::texture::funcs::set_box);
}
