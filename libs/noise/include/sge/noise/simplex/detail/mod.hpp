//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_NOISE_SIMPLEX_DETAIL_MOD_HPP_INCLUDED
#define SGE_NOISE_SIMPLEX_DETAIL_MOD_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>

namespace sge::noise::simplex::detail
{

inline std::size_t
mod(long const &a, // NOLINT(google-runtime-int)
    std::size_t const &b)
{
  if (a >= 0)
  {
    return static_cast<std::size_t>(a) % static_cast<std::size_t>(b);
  }

  return static_cast<std::size_t>(-a) % static_cast<std::size_t>(b);
}

}

#endif
