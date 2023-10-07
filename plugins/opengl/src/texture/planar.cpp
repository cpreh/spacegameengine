//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/context/use.hpp>
#include <sge/opengl/texture/basic_parameters.hpp>
#include <sge/opengl/texture/planar.hpp>
#include <sge/opengl/texture/planar_basic.hpp>
#include <sge/opengl/texture/planar_types.hpp> // NOLINT(misc-include-cleaner)
#include <sge/opengl/texture/surface_context.hpp>
#include <sge/opengl/texture/convert/make_type.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/texture/planar.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/texture/planar_parameters_fwd.hpp>
#include <fcppt/make_ref.hpp>

sge::opengl::texture::planar::planar(
    sge::opengl::texture::basic_parameters const &_basic_parameters,
    sge::renderer::texture::planar_parameters const &_parameters)
    : sge::opengl::texture::planar_basic(
          _basic_parameters,
          sge::opengl::texture::convert::make_type(GL_TEXTURE_2D),
          _parameters,
          sge::opengl::context::use<sge::opengl::texture::surface_context>(
              fcppt::make_ref(_basic_parameters.context()))
              .config())
{
}

sge::opengl::texture::planar::~planar() = default;
