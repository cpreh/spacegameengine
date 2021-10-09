//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/texture/basic_parameters_fwd.hpp>
#include <sge/opengl/texture/create_depth_stencil.hpp>
#include <sge/opengl/texture/depth_stencil.hpp>
#include <sge/renderer/texture/depth_stencil.hpp>
#include <sge/renderer/texture/depth_stencil_parameters_fwd.hpp>
#include <sge/renderer/texture/depth_stencil_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>

sge::renderer::texture::depth_stencil_unique_ptr sge::opengl::texture::create_depth_stencil(
    sge::opengl::texture::basic_parameters const &_basic_parameters,
    sge::renderer::texture::depth_stencil_parameters const &_parameters)
{
  return fcppt::unique_ptr_to_base<sge::renderer::texture::depth_stencil>(
      fcppt::make_unique_ptr<sge::opengl::texture::depth_stencil>(_basic_parameters, _parameters));
}
