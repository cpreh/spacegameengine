#ifndef SGE_ODE_SHAPES_BOX_HPP_INCLUDED
#define SGE_ODE_SHAPES_BOX_HPP_INCLUDED

#include "../transformer_fwd.hpp"
#include "base.hpp"
#include <sge/collision/dim.hpp>
#include <sge/collision/shapes/box.hpp>

namespace sge
{
namespace ode
{
namespace shapes
{
class box
:
	public collision::shapes::box,
	public ode::shapes::base
{
public:
	box(
		transformer const &,
		dSpaceID,
		collision::dim const &);

	collision::dim const 
	dim() const;

	void 
	dim(
		collision::dim const &);
private:
	transformer const &transformer_;
};
}
}
}

#endif
