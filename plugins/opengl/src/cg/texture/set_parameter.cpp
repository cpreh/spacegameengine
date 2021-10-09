//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/cg/check_state.hpp>
#include <sge/cg/parameter/object.hpp>
#include <sge/opengl/cg/texture/set_parameter.hpp>
#include <sge/opengl/texture/no_id.hpp>
#include <sge/opengl/texture/optional_id.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/const.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cgGL.h>
#include <fcppt/config/external_end.hpp>

void sge::opengl::cg::texture::set_parameter(
    sge::cg::parameter::object const &_parameter, sge::opengl::texture::optional_id const &_id)
{
  ::cgGLSetTextureParameter(
      _parameter.get(),
      fcppt::optional::from(_id, fcppt::const_(sge::opengl::texture::no_id)).get());

  SGE_CG_CHECK_STATE(FCPPT_TEXT("cgGLSetTextureParameter failed"), sge::renderer::exception)
}
