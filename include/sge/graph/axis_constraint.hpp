#ifndef SGE_GRAPH_AXIS_CONSTRAINT_HPP_INCLUDED
#define SGE_GRAPH_AXIS_CONSTRAINT_HPP_INCLUDED

#include <sge/graph/symbol.hpp>
#include <sge/graph/scalar.hpp>

namespace sge
{
namespace graph
{
class axis_constraint
{
public:
	SGE_GRAPH_SYMBOL
	axis_constraint(
		sge::graph::scalar min,
		sge::graph::scalar max);

	SGE_GRAPH_SYMBOL
	sge::graph::scalar
	min() const;

	SGE_GRAPH_SYMBOL
	sge::graph::scalar
	max() const;
private:
	sge::graph::scalar min_;
	sge::graph::scalar max_;
};
}
}

#endif
