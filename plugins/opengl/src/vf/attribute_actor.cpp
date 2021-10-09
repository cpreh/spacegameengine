//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/common.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/vf/actor_parameters.hpp>
#include <sge/opengl/vf/attribute_actor.hpp>
#include <sge/opengl/vf/attribute_config.hpp>
#include <sge/opengl/vf/attribute_context.hpp>
#include <sge/opengl/vf/client_state_combiner.hpp>
#include <sge/opengl/vf/client_state_combiner_ref.hpp>
#include <sge/opengl/vf/extra_elements.hpp>
#include <sge/opengl/vf/extra_format.hpp>
#include <sge/opengl/vf/extra_index.hpp>
#include <sge/opengl/vf/get_attribute_config.hpp>
#include <sge/opengl/vf/pointer.hpp>
#include <sge/opengl/vf/pointer_actor.hpp>
#include <sge/opengl/vf/vertex_attrib_pointer.hpp>
#include <sge/renderer/vf/dynamic/extra.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>

sge::opengl::vf::attribute_actor::attribute_actor(
    sge::opengl::vf::actor_parameters const &_param,
    sge::renderer::vf::dynamic::extra const &_extra)
    : sge::opengl::vf::pointer_actor(_param),
      attribute_config_(sge::opengl::vf::get_attribute_config(
          sge::opengl::context::use<sge::opengl::vf::attribute_context>(
              fcppt::make_ref(_param.context()), _param.context().info()))),
      elements_(sge::opengl::vf::extra_elements(_extra.type())),
      format_(sge::opengl::vf::extra_format(_extra.type())),
      location_(fcppt::cast::size<GLuint>(sge::opengl::vf::extra_index(_extra.index())))
{
}

sge::opengl::vf::attribute_actor::~attribute_actor() = default;

void sge::opengl::vf::attribute_actor::operator()(
    sge::opengl::vf::client_state_combiner_ref const _combiner,
    sge::opengl::vf::pointer const _src) const
{
  _combiner.get().enable_attribute(location_);

  sge::opengl::vf::vertex_attrib_pointer(
      attribute_config_.get(),
      location_,
      elements_,
      format_,
      GL_TRUE, // normalized
      fcppt::cast::size<GLsizei>(fcppt::cast::to_signed(this->stride().get())),
      _src);
}

void sge::opengl::vf::attribute_actor::unuse(
    sge::opengl::vf::client_state_combiner_ref const _combiner) const
{
  _combiner.get().disable_attribute(location_);
}
