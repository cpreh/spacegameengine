//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/graph/axis_constraint.hpp>

sge::graph::axis_constraint::axis_constraint(
    sge::graph::scalar const _min, sge::graph::scalar const _max)
    : min_(_min), max_(_max)
{
}

sge::graph::scalar sge::graph::axis_constraint::min() const { return min_; }

sge::graph::scalar sge::graph::axis_constraint::max() const { return max_; }
