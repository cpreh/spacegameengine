//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/audio/player.hpp>
#include <sge/audio/player_unique_ptr.hpp>
#include <sge/audio/player_plugin/traits.hpp>
#include <sge/audio_null/player.hpp>
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

// NOLINTNEXTLINE(cert-err58-cpp,fuchsia-statically-constructed-objects)
sge::plugin::info const info{
    sge::plugin::name(FCPPT_TEXT("audio_null")),
    sge::plugin::description(FCPPT_TEXT("An audio plugin that does not do anything.")),
    sge::plugin::version(0x1U),
    sge::plugin::min_core_version(0x1U),
    sge::plugin::capabilities_field{sge::plugin::capabilities::audio_player},
    sge::plugin::flags_field::null()};

FCPPT_PP_POP_WARNING

sge::audio::player_unique_ptr create_audio_player(fcppt::log::context_reference)
{
  return fcppt::unique_ptr_to_base<sge::audio::player>(
      fcppt::make_unique_ptr<sge::audio_null::player>());
}

}

// NOLINTNEXTLINE(cert-err58-cpp,fuchsia-statically-constructed-objects)
SGE_PLUGIN_LIBRARY_MAKE_INTERFACE(info, ((sge::audio::player, create_audio_player)))
