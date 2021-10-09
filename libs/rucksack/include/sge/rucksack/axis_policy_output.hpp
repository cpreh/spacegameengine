//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RUCKSACK_AXIS_POLICY_OUTPUT_HPP_INCLUDED
#define SGE_RUCKSACK_AXIS_POLICY_OUTPUT_HPP_INCLUDED

#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/minimum_size.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ostream>
#include <fcppt/config/external_end.hpp>

namespace sge::rucksack
{

template <typename Ch, typename Traits>
std::basic_ostream<Ch, Traits> &
operator<<(std::basic_ostream<Ch, Traits> &_stream, sge::rucksack::axis_policy const &_policy)
{
  fcppt::variant::match(
      _policy,
      [&_stream](sge::rucksack::minimum_size const _min) { _stream << _stream.widen('m') << _min; },
      [&_stream](sge::rucksack::preferred_size const _pref)
      { _stream << _stream.widen('p') << _pref; });

  return _stream;
}

}

#endif
