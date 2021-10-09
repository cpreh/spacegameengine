//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

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
#include <sge/wlinput/system.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/context_reference.hpp>

namespace
{

// NOLINTNEXTLINE(fuchsia-statically-constructed-objects,cert-err58-cpp)
sge::plugin::info const info(
    sge::plugin::name(FCPPT_TEXT("wlinput")),
    sge::plugin::description(FCPPT_TEXT("Uses Wayland seats to handle foci and cursors.")),
    sge::plugin::version(0x1U),
    sge::plugin::min_core_version(0x1U),
    sge::plugin::capabilities_field{sge::plugin::capabilities::input},
    sge::plugin::flags_field{});

sge::input::system_unique_ptr create_input_system(fcppt::log::context_reference const _log_context)
{
  return fcppt::unique_ptr_to_base<sge::input::system>(
      fcppt::make_unique_ptr<sge::wlinput::system>(_log_context));
}

}

// NOLINTNEXTLINE(fuchsia-statically-constructed-objects,cert-err58-cpp)
SGE_PLUGIN_LIBRARY_MAKE_INTERFACE(info, ((sge::input::system, create_input_system)))
