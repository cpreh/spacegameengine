//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_LIBPNG_FORMAT_HPP_INCLUDED
#define SGE_LIBPNG_FORMAT_HPP_INCLUDED

#include <sge/libpng/format_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::libpng
{

enum class format : std::uint8_t
{
  l8,
  la8,
  srgb8,
  sbgr8,
  srgba8,
  sbgra8
};

}

#endif
