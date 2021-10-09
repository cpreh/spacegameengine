//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/window/dim.hpp>
#include <sge/window/event_combiner.hpp>
#include <sge/window/event_function.hpp>
#include <sge/window/object.hpp>
#include <sge/window/system.hpp>
#include <sge/window/system_event_function.hpp>
#include <sge/window/system_ref.hpp>
#include <awl/event/base.hpp>
#include <awl/event/container.hpp>
#include <awl/window/object.hpp>
#include <awl/window/reference.hpp>
#include <awl/window/event/base.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::window::object::object(
    sge::window::system_ref const _system, awl::window::reference const _awl_window)
    : system_{_system},
      awl_object_{_awl_window},
      event_signal_{event_signal::combiner_function{&sge::window::event_combiner}},
      connection_{this->system().event_handler(sge::window::system_event_function{
          [this](awl::event::base const &_event)
          {
            return fcppt::optional::maybe(
                fcppt::cast::dynamic<awl::window::event::base const>(_event),
                [] { return awl::event::container{}; },
                [this](fcppt::reference<awl::window::event::base const> const _ref) {
                  return this->event_signal_(
                      event_signal::initial_value{awl::event::container{}}, _ref.get());
                });
          }})}
{
}

FCPPT_PP_POP_WARNING

sge::window::object::~object() = default;

sge::window::dim sge::window::object::size() const
{
  return fcppt::math::dim::structure_cast<sge::window::dim, fcppt::cast::size_fun>(
      this->awl_object().size());
}

void sge::window::object::show() // NOLINT(readability-make-member-function-const)
{
  this->awl_object().show();
}

awl::window::object &sge::window::object::awl_object() const { return this->awl_object_.get(); }

fcppt::signal::auto_connection
sge::window::object::event_handler(sge::window::event_function _function)
{
  return this->event_signal_.connect(std::move(_function));
}

sge::window::system &sge::window::object::system() const { return this->system_.get(); }
