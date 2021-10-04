//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GRAPH_AXIS_CONSTRAINT_HPP_INCLUDED
#define SGE_GRAPH_AXIS_CONSTRAINT_HPP_INCLUDED

#include <sge/graph/axis_constraint_fwd.hpp>
#include <sge/graph/scalar.hpp>
#include <sge/graph/detail/symbol.hpp>


namespace sge::graph
{

class axis_constraint
{
public:
	SGE_GRAPH_DETAIL_SYMBOL
	axis_constraint(
		sge::graph::scalar min,
		sge::graph::scalar max
	);

	[[nodiscard]]
	SGE_GRAPH_DETAIL_SYMBOL
	sge::graph::scalar
	min() const;

	[[nodiscard]]
	SGE_GRAPH_DETAIL_SYMBOL
	sge::graph::scalar
	max() const;
private:
	sge::graph::scalar min_;
	sge::graph::scalar max_;
};

}

#endif
