#include <sge/graph/axis_constraint.hpp>

sge::graph::axis_constraint::axis_constraint(
	sge::graph::scalar const _min,
	sge::graph::scalar const _max)
:
	min_(
		_min),
	max_(
		_max)
{
}

sge::graph::scalar
sge::graph::axis_constraint::min() const
{
	return
		min_;
}

sge::graph::scalar
sge::graph::axis_constraint::max() const
{
	return
		max_;
}
