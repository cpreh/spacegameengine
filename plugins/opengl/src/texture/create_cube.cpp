//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/context/object.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/texture/basic_parameters.hpp>
#include <sge/opengl/texture/create_cube.hpp>
#include <sge/opengl/texture/cube.hpp>
#include <sge/opengl/texture/cube_context.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/texture/cube.hpp>
#include <sge/renderer/texture/cube_parameters_fwd.hpp>
#include <sge/renderer/texture/cube_unique_ptr.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/optional/to_exception.hpp>

sge::renderer::texture::cube_unique_ptr sge::opengl::texture::create_cube(
    sge::opengl::texture::basic_parameters const &_basic_parameters,
    sge::renderer::texture::cube_parameters const &_parameters)
{
  return fcppt::unique_ptr_to_base<sge::renderer::texture::cube>(
      fcppt::make_unique_ptr<sge::opengl::texture::cube>(
          fcppt::optional::to_exception(
              sge::opengl::context::use<sge::opengl::texture::cube_context>(
                  fcppt::make_ref(_basic_parameters.context()), _basic_parameters.context().info())
                  .config(),
              []
              {
                return sge::renderer::unsupported{
                    FCPPT_TEXT("cube texture"),
                    FCPPT_TEXT("1.3"),
                    FCPPT_TEXT("gl_arb_texture_cube")};
              }),
          _basic_parameters,
          _parameters));
}
