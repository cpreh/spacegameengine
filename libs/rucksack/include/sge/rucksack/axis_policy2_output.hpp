//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RUCKSACK_AXIS_POLICY2_OUTPUT_HPP_INCLUDED
#define SGE_RUCKSACK_AXIS_POLICY2_OUTPUT_HPP_INCLUDED

#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/axis_policy_output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ostream>
#include <fcppt/config/external_end.hpp>

namespace sge::rucksack
{

template <typename Ch, typename Traits>
std::basic_ostream<Ch, Traits> &
operator<<(std::basic_ostream<Ch, Traits> &_stream, sge::rucksack::axis_policy2 const &_policy)
{
  return _stream << _stream.widen('(') << _policy.x() << _stream.widen(',') << _policy.y()
                 << _stream.widen(')');
}

}

#endif
