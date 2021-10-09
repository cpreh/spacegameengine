//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/common.hpp>
#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/vf/actor.hpp>
#include <sge/opengl/vf/client_state_combiner.hpp>
#include <sge/opengl/vf/part.hpp>
#include <sge/opengl/vf/pointer.hpp>
#include <sge/opengl/vf/to_actor.hpp>
#include <sge/renderer/vf/dynamic/ordered_element_fwd.hpp>
#include <sge/renderer/vf/dynamic/part.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/cast/from_void_ptr.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::opengl::vf::part::part(
    fcppt::log::object_reference const _log,
    sge::opengl::context::object_ref const _context,
    sge::renderer::vf::dynamic::part &&_part)
    : log_{_log},
      context_(_context),
      part_(std::move(_part)),
      actors_(fcppt::algorithm::map<actor_container>(
          this->part_.elements(),
          [this](sge::renderer::vf::dynamic::ordered_element const &_elem) {
            return sge::opengl::vf::to_actor(
                this->log_, _elem, this->part_.stride(), this->context_);
          }))
{
}

sge::opengl::vf::part::~part() = default;

sge::renderer::vf::dynamic::part const &sge::opengl::vf::part::get() const { return part_; }

void sge::opengl::vf::part::use_me(sge::opengl::vf::pointer const _src) const
{
  sge::opengl::vf::client_state_combiner states(log_, context_);

  for (auto const &actor : actors_)
  {
    (*actor)(
        fcppt::make_ref(states),
        fcppt::cast::from_void_ptr<unsigned char const *>(_src) + actor->offset().get());
  }
}

void sge::opengl::vf::part::unuse_me() const
{
  sge::opengl::vf::client_state_combiner states(log_, context_);

  for (auto const &actor : actors_)
  {
    actor->unuse(fcppt::make_ref(states));
  }
}
