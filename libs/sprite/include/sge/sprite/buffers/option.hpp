//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_BUFFERS_OPTION_HPP_INCLUDED
#define SGE_SPRITE_BUFFERS_OPTION_HPP_INCLUDED

#include <sge/sprite/buffers/option_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::sprite::buffers
{

enum class option : std::uint8_t
{
  dynamic,
  static_
};

}

#endif
