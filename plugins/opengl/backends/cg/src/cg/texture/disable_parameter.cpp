//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/cg/check_state.hpp>
#include <sge/cg/parameter/object.hpp>
#include <sge/opengl/cg/texture/disable_parameter.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cgGL.h>
#include <fcppt/config/external_end.hpp>

void sge::opengl::cg::texture::disable_parameter(sge::cg::parameter::object const &_parameter)
{
  ::cgGLDisableTextureParameter(_parameter.get());

  SGE_CG_CHECK_STATE(FCPPT_TEXT("cgEnableTextureParameter failed"), sge::renderer::exception)
}
