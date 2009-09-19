#ifndef SGE_ODE_SHAPES_CIRCLE_HPP_INCLUDED
#define SGE_ODE_SHAPES_CIRCLE_HPP_INCLUDED

#include "base.hpp"
#include "../transformer_fwd.hpp"
#include <sge/collision/shapes/circle.hpp>

namespace sge
{
namespace ode
{
namespace shapes
{
class circle
:
	public sge::collision::shapes::circle,
	public ode::shapes::base
{
public:
	circle(
		transformer const &,
		dSpaceID,
		collision::unit);
	collision::unit radius() const;
	void radius(
		collision::unit);
private:
	transformer const &transformer_;
};
}
}
}

#endif