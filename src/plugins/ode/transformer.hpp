#ifndef SGE_ODE_TRANSFORMER_HPP_INCLUDED
#define SGE_ODE_TRANSFORMER_HPP_INCLUDED

#include "point.hpp"
#include "dim.hpp"
#include <sge/collision/optional_box.hpp>
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
	inline transformer(
		sge::collision::optional_box const &);
	collision::point const
	inline position_from_ode(
		point const &) const;
	inline collision::point const
	velocity_from_ode(
		point const &) const;
	inline collision::dim const
	dim_from_ode(
		dim const &) const;
	inline point const 
	position_to_ode(
		collision::point const &) const;
	inline sge::ode::dim const 
	dim_to_ode(
		sge::collision::dim const &) const;
	inline point const 
	velocity_to_ode(
		collision::point const &) const;
	inline collision::unit 
	unit_from_ode(
		dReal) const;
	inline dReal 
	unit_to_ode(
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
