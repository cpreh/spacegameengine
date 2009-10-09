#ifndef SGE_ODE_SHAPES_SPHERE_HPP_INCLUDED
#define SGE_ODE_SHAPES_SPHERE_HPP_INCLUDED

#include "base.hpp"
#include "../transformer_fwd.hpp"
#include <sge/collision/shapes/sphere.hpp>

namespace sge
{
namespace ode
{
namespace shapes
{
class sphere
:
	public sge::collision::shapes::sphere,
	public ode::shapes::base
{
public:
	sphere(
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
