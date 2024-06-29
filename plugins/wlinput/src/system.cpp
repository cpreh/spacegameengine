//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/capabilities.hpp>
#include <sge/input/capabilities_field.hpp>
#include <sge/input/processor.hpp>
#include <sge/input/processor_unique_ptr.hpp>
#include <sge/input/system.hpp>
#include <sge/log/location.hpp>
#include <sge/window/object_ref.hpp>
#include <sge/wlinput/processor.hpp>
#include <sge/wlinput/system.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/log/name.hpp>

sge::wlinput::system::system(fcppt::log::context_reference const _log_context)
    : sge::input::system(),
      log_{_log_context, sge::log::location(), fcppt::log::name{FCPPT_TEXT("wlinput")}}
{
}

sge::wlinput::system::~system() = default;

sge::input::processor_unique_ptr
sge::wlinput::system::create_processor(sge::window::object_ref const _window)
{
  return fcppt::unique_ptr_to_base<sge::input::processor>(
      fcppt::make_unique_ptr<sge::wlinput::processor>(fcppt::make_ref(log_), _window));
}

sge::input::capabilities_field sge::wlinput::system::capabilities() const
{
  return sge::input::capabilities_field{
      sge::input::capabilities::cursor, sge::input::capabilities::focus};
}
