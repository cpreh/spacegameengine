//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/font/system.hpp>
#include <sge/font/system_unique_ptr.hpp>
#include <sge/font/plugin/traits.hpp>
#include <sge/gdifont/system.hpp>
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
#include <fcppt/log/context_fwd.hpp>


namespace
{

sge::plugin::info const info(
	sge::plugin::name(
		FCPPT_TEXT("gdifont")
	),
	sge::plugin::description(
		FCPPT_TEXT("Renders fonts using the Windows API.")
	),
	sge::plugin::version(0x1u),
	sge::plugin::min_core_version(0x1u),
	sge::plugin::capabilities_field{
		sge::plugin::capabilities::font
	},
	sge::plugin::flags_field::null()
);

sge::font::system_unique_ptr
create_font_system(
	fcppt::log::context &
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::font::system
		>(
			fcppt::make_unique_ptr<
				sge::gdifont::system
			>()
		);
}

}

SGE_PLUGIN_LIBRARY_MAKE_INTERFACE(
	info,
	(
		(
			sge::font::system,
			create_font_system
		)
	)
)
