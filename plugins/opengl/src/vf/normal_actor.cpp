//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/call.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/vf/actor_parameters_fwd.hpp>
#include <sge/opengl/vf/convert_element_type.hpp>
#include <sge/opengl/vf/fp_actor.hpp>
#include <sge/opengl/vf/normal_actor.hpp>
#include <sge/opengl/vf/pointer.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/vf/dynamic/normal.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>

sge::opengl::vf::normal_actor::normal_actor(
    sge::opengl::vf::actor_parameters const &_param,
    sge::renderer::vf::dynamic::normal const &_normal)
    : sge::opengl::vf::fp_actor(_param, GL_NORMAL_ARRAY),
      format_(sge::opengl::vf::convert_element_type(_normal.element_type()))
{
}

sge::opengl::vf::normal_actor::~normal_actor() = default;

void sge::opengl::vf::normal_actor::on_use(sge::opengl::vf::pointer const _src) const
{
  sge::opengl::call(
      ::glNormalPointer,
      format_,
      fcppt::cast::size<GLsizei>(fcppt::cast::to_signed(this->stride().get())),
      _src);

  SGE_OPENGL_CHECK_STATE(FCPPT_TEXT("glNormalPointer failed"), sge::renderer::exception)
}
