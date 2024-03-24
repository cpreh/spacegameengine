//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SYSTEMS_DETAIL_ANY_KEY_HPP_INCLUDED
#define SGE_SYSTEMS_DETAIL_ANY_KEY_HPP_INCLUDED

#include <sge/systems/detail/any_key_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::systems::detail
{

enum class any_key : std::uint8_t
{
  config,
  window,
  renderer,
  image2d,
  audio_loader,
  audio_player,
  input,
  font,
  fcppt_maximum = font
};

}

#endif
