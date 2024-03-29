//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RUCKSACK_AXIS_POLICY_FWD_HPP_INCLUDED
#define SGE_RUCKSACK_AXIS_POLICY_FWD_HPP_INCLUDED

#include <sge/rucksack/minimum_size_fwd.hpp>
#include <sge/rucksack/preferred_size_fwd.hpp>
#include <fcppt/variant/object_fwd.hpp>

namespace sge::rucksack
{

using axis_policy =
    fcppt::variant::object<sge::rucksack::minimum_size, sge::rucksack::preferred_size>;

}

#endif
