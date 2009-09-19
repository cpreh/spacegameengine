#ifndef SGE_ODE_TRANSFORMER_HPP_INCLUDED
#define SGE_ODE_TRANSFORMER_HPP_INCLUDED

#include "point.hpp"
#include "dim.hpp"
#include <sge/collision/optional_rect.hpp>
#include <sge/collision/point.hpp>
#include <sge/math/vector/basic_decl.hpp>
#include <sge/collision/dim.hpp>

namespace sge
{
namespace ode
{
class transformer
{
public:
	transformer(
		sge::collision::optional_rect const &);
	collision::point const
	from_ode(
		point const &) const;
	collision::dim const
	from_ode(
		dim const &) const;
	point const to_ode(
		collision::point const &) const;
	dim const to_ode(
		collision::dim const &) const;
	collision::unit from_ode(
		dReal) const;
	dReal to_ode(
		collision::unit) const;
private:
	sge::collision::unit
		scaling_,
		inverse_scaling_;
	sge::collision::point 
		translation_;
};
}
}

#endif