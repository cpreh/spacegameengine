//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PLUGIN_CAPABILITIES_HPP_INCLUDED
#define SGE_PLUGIN_CAPABILITIES_HPP_INCLUDED

#include <sge/plugin/capabilities_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::plugin
{

enum class capabilities : std::uint8_t
{
  renderer,
  input,
  image2d_system,
  audio_player,
  font,
  audio_loader
};

}

FCPPT_ENUM_DEFINE_MAX_VALUE(sge::plugin::capabilities::audio_loader);

#endif
