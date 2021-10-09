//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/libpng/compare_gamma.hpp>
#include <sge/libpng/gamma.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/math/diff.hpp>

bool sge::libpng::compare_gamma(sge::libpng::gamma const _left, sge::libpng::gamma const _right)
{
  return fcppt::math::diff(
             _left.get(),
             _right.get()) <
         fcppt::literal<sge::libpng::gamma::value_type>(
             0.01 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
         );
}
