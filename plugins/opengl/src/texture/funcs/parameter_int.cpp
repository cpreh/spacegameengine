//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/call.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/texture/binding.hpp>
#include <sge/opengl/texture/funcs/parameter_int.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <fcppt/text.hpp>

void sge::opengl::texture::funcs::parameter_int(
    sge::opengl::texture::binding const &_binding, GLenum const _name, GLint const _value)
{
  sge::opengl::call(::glTexParameteri, _binding.type().get(), _name, _value);

  SGE_OPENGL_CHECK_STATE(FCPPT_TEXT("glTexParameteri failed"), sge::renderer::exception)
}
