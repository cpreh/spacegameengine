//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/call.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/texture/no_id.hpp>
#include <sge/opengl/texture/optional_id.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/opengl/texture/funcs/bind.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <fcppt/const.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/from.hpp>

void sge::opengl::texture::funcs::bind(
    sge::opengl::texture::type const _type, sge::opengl::texture::optional_id const &_value)
{
  sge::opengl::call(
      ::glBindTexture,
      _type.get(),
      fcppt::optional::from(_value, fcppt::const_(sge::opengl::texture::no_id)).get());

  SGE_OPENGL_CHECK_STATE(FCPPT_TEXT("glBindTexture failed"), sge::renderer::exception)
}
