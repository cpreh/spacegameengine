//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/vf/actor_parameters_fwd.hpp>
#include <sge/opengl/vf/client_state_combiner.hpp> // NOLINT(misc-include-cleaner)
#include <sge/opengl/vf/client_state_combiner_ref.hpp>
#include <sge/opengl/vf/fp_actor.hpp>
#include <sge/opengl/vf/pointer.hpp>
#include <sge/opengl/vf/pointer_actor.hpp>
#include <sge/renderer/opengl/glinclude.hpp>

sge::opengl::vf::fp_actor::~fp_actor() = default;

sge::opengl::vf::fp_actor::fp_actor(
    sge::opengl::vf::actor_parameters const &_param, GLenum const _client_state)
    : sge::opengl::vf::pointer_actor(_param), client_state_(_client_state)
{
}

void sge::opengl::vf::fp_actor::operator()(
    sge::opengl::vf::client_state_combiner_ref const _combiner,
    sge::opengl::vf::pointer const _src) const
{
  this->on_use(_src);

  _combiner.get().enable(client_state_);
}

void sge::opengl::vf::fp_actor::unuse(
    sge::opengl::vf::client_state_combiner_ref const _combiner) const
{
  _combiner.get().disable(client_state_);
}
