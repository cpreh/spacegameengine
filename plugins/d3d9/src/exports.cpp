//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/core.hpp>
#include <sge/plugin/capabilities.hpp>
#include <sge/plugin/capabilities_field.hpp>
#include <sge/plugin/description.hpp>
#include <sge/plugin/flags.hpp>
#include <sge/plugin/flags_field.hpp>
#include <sge/plugin/info.hpp>
#include <sge/plugin/min_core_version.hpp>
#include <sge/plugin/name.hpp>
#include <sge/plugin/version.hpp>
#include <sge/plugin/library/make_interface.hpp>
#include <sge/renderer/core.hpp>
#include <sge/renderer/core_unique_ptr.hpp>
#include <sge/renderer/plugin/traits.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/context_reference.hpp>

namespace
{

sge::plugin::info const info(
    sge::plugin::name(FCPPT_TEXT("d3d9")),
    sge::plugin::description(FCPPT_TEXT("Implements a renderer using Direct3D9.")),
    sge::plugin::version(0x1u),
    sge::plugin::min_core_version(0x1u),
    sge::plugin::capabilities_field{sge::plugin::capabilities::renderer},
    sge::plugin::flags_field::null());

sge::renderer::core_unique_ptr
create_renderer_core(fcppt::log::context_reference const _log_context)
{
  return fcppt::unique_ptr_to_base<sge::renderer::core>(
      fcppt::make_unique_ptr<sge::d3d9::core>(_log_context));
}

}

SGE_PLUGIN_LIBRARY_MAKE_INTERFACE(info, ((sge::renderer::core, create_renderer_core)))
