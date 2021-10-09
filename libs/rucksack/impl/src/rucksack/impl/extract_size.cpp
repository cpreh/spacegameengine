//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/minimum_size.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/impl/extract_size.hpp>
#include <fcppt/variant/match.hpp>

sge::rucksack::scalar sge::rucksack::impl::extract_size(sge::rucksack::axis_policy const &_policy)
{
  return fcppt::variant::match(
      _policy,
      [](sge::rucksack::minimum_size const _pol) { return _pol.get(); },
      [](sge::rucksack::preferred_size const _pol) { return _pol.get(); });
}
