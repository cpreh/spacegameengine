//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/libpng/gamma.hpp>
#include <sge/libpng/srgb_gamma.hpp>
#include <fcppt/literal.hpp>

sge::libpng::gamma sge::libpng::srgb_gamma()
{
  return sge::libpng::gamma(fcppt::literal<sge::libpng::gamma::value_type>(
      0.45455 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      ));
}
