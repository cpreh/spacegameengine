//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/audio/loader.hpp>
#include <sge/audio/loader_unique_ptr.hpp>
#include <sge/audio/loader_plugin/traits.hpp>
#include <sge/plugin/capabilities.hpp>
#include <sge/plugin/capabilities_field.hpp>
#include <sge/plugin/description.hpp>
#include <sge/plugin/flags_field.hpp>
#include <sge/plugin/info.hpp>
#include <sge/plugin/min_core_version.hpp>
#include <sge/plugin/name.hpp>
#include <sge/plugin/version.hpp>
#include <sge/plugin/library/make_interface.hpp>
#include <sge/vorbis/loader.hpp>
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
	sge::plugin::name(
		FCPPT_TEXT("vorbis")
	),
	sge::plugin::description(
		FCPPT_TEXT("Loads vorbis files.")
	),
	sge::plugin::version(0x1U),
	sge::plugin::min_core_version(0x1U),
	sge::plugin::capabilities_field{
		sge::plugin::capabilities::audio_loader
	},
	sge::plugin::flags_field::null()
);

FCPPT_PP_POP_WARNING

sge::audio::loader_unique_ptr
create_audio_loader(
	fcppt::log::context_reference const _log_context
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::audio::loader
		>(
			fcppt::make_unique_ptr<
				sge::vorbis::loader
			>(
				_log_context
			)
		);
}

}

// NOLINTNEXTLINE(fuchsia-statically-constructed-objects,cert-err58-cpp)
SGE_PLUGIN_LIBRARY_MAKE_INTERFACE(
	info,
	(
		(
			sge::audio::loader,
			create_audio_loader
		)
	)
)
