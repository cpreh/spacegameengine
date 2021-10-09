//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PLUGIN_CAPABILITIES_HPP_INCLUDED
#define SGE_PLUGIN_CAPABILITIES_HPP_INCLUDED

#include <sge/plugin/capabilities_fwd.hpp>

namespace sge::plugin
{

enum class capabilities
{
  renderer,
  input,
  image2d_system,
  audio_player,
  font,
  audio_loader,
  fcppt_maximum = audio_loader
};

}

#endif
