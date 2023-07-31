//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/graph/axis_constraint.hpp>
#include <sge/graph/scalar.hpp>

sge::graph::axis_constraint::axis_constraint(min_type const _min, max_type const _max)
    : min_{_min.get()}, max_{_max.get()}
{
}

sge::graph::scalar sge::graph::axis_constraint::min() const { return this->min_; }

sge::graph::scalar sge::graph::axis_constraint::max() const { return this->max_; }
