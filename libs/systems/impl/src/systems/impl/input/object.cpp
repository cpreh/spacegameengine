//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/capabilities.hpp>
#include <sge/input/capabilities_field.hpp>
#include <sge/input/capabilities_to_string.hpp>
#include <sge/input/create_multi_system.hpp>
#include <sge/input/processor.hpp>
#include <sge/input/system.hpp>
#include <sge/input/plugin/collection_fwd.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/impl/input/cursor_modifier.hpp>
#include <sge/systems/impl/input/cursor_modifier_unique_ptr.hpp>
#include <sge/systems/impl/input/object.hpp>
#include <sge/systems/impl/window/object.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/bitfield/comparison.hpp>
#include <fcppt/container/bitfield/operators.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::systems::impl::input::object::object(
    fcppt::log::context_reference const _log_context,
    fcppt::log::object &_log,
    sge::input::plugin::collection const &_collection,
    sge::systems::input const &_parameters,
    sge::systems::impl::window::object const &_window_object)
    : input_system_{sge::input::create_multi_system(_log_context, _collection)},
      input_processor_{input_system_->create_processor(fcppt::make_ref(_window_object.get()))},
      cursor_modifier_{fcppt::optional::make_if(
          _parameters.cursor_options() != sge::systems::cursor_option_field::null(),
          [&_window_object, &_parameters, this]
          {
            return fcppt::make_unique_ptr<sge::systems::impl::input::cursor_modifier>(
                *this->input_processor_,
                fcppt::make_ref(_window_object.get()),
                _parameters.cursor_options());
          })}
{
  for (sge::input::capabilities const element :
       {sge::input::capabilities::cursor,
        sge::input::capabilities::keyboard,
        sge::input::capabilities::mouse})
  {
    if (!(input_system_->capabilities() & element))
    {
      FCPPT_LOG_WARNING(
          _log,
          fcppt::log::out << FCPPT_TEXT("None of your input plugins handles capability ")
                          << sge::input::capabilities_to_string(element))
    }
  }
}

FCPPT_PP_POP_WARNING

sge::systems::impl::input::object::~object() = default;

sge::input::system &sge::systems::impl::input::object::system() const { return *input_system_; }

sge::input::processor &sge::systems::impl::input::object::processor() const
{
  return *input_processor_;
}
