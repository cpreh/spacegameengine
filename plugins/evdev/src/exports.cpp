//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/evdev/system.hpp>
#include <sge/input/system.hpp>
#include <sge/input/system_unique_ptr.hpp>
#include <sge/input/plugin/traits.hpp>
#include <sge/plugin/capabilities.hpp>
#include <sge/plugin/capabilities_field.hpp>
#include <sge/plugin/description.hpp>
#include <sge/plugin/flags_field.hpp>
#include <sge/plugin/info.hpp>
#include <sge/plugin/min_core_version.hpp>
#include <sge/plugin/name.hpp>
#include <sge/plugin/version.hpp>
#include <sge/plugin/library/make_interface.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

namespace
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)
FCPPT_PP_DISABLE_CLANG_WARNING(-Wexit-time-destructors)

// NOLINTNEXTLINE(fuchsia-statically-constructed-objects,cert-err58-cpp)
sge::plugin::info const info(
    sge::plugin::name(FCPPT_TEXT("evdev")),
    sge::plugin::description(
        FCPPT_TEXT("Uses /dev/input/event* to handle joysticks and gamepads.")),
    sge::plugin::version(0x1U),
    sge::plugin::min_core_version(0x1U),
    sge::plugin::capabilities_field{sge::plugin::capabilities::input},
    sge::plugin::flags_field::null());

FCPPT_PP_POP_WARNING

sge::input::system_unique_ptr create_input_system(fcppt::log::context_reference const _log_context)
{
  return fcppt::unique_ptr_to_base<sge::input::system>(
      fcppt::make_unique_ptr<sge::evdev::system>(_log_context));
}

}

// NOLINTNEXTLINE(fuchsia-statically-constructed-objects,cert-err58-cpp)
SGE_PLUGIN_LIBRARY_MAKE_INTERFACE(info, ((sge::input::system, create_input_system)))
