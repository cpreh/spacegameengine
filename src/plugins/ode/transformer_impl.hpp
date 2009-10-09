#include <sge/math/inverse.hpp>
#include <sge/math/box/basic_impl.hpp>
#include <sge/math/vector/structure_cast.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/math/dim/structure_cast.hpp>
#include <sge/math/dim/arithmetic.hpp>
#include <sge/optional.hpp>
#include <sge/math/null.hpp>
#include <algorithm>

//DEBUG
#include <sge/cerr.hpp>
#include <sge/math/vector/output.hpp>

namespace
{
sge::collision::unit calculate_scaling(
	sge::collision::optional_rect const &_r)
{
	if (!_r)
		return 
			static_cast<sge::collision::unit>(
				1);
				
	return 
		static_cast<sge::collision::unit>(
			sge::math::inverse<sge::collision::unit>(
				std::max(
					_r->dim().w(),
					_r->dim().h())));
}
}


sge::ode::transformer::transformer(
	collision::optional_rect const &_r)
:
	scaling_(
		calculate_scaling(
			_r)),
	inverse_scaling_(
		math::inverse(
			scaling_)),
	translation_(
		_r 
		? 
			collision::point(
				-_r->pos().x(),
				-_r->pos().y(),
				math::null<collision::unit>())
		:
			collision::point::null())
{
}

sge::collision::point const
sge::ode::transformer::position_from_ode(
	point const &_p) const
{
	return 
		math::vector::structure_cast<collision::point>(
			_p*
			static_cast<dReal>(
				inverse_scaling_)-
			sge::math::vector::structure_cast<point>(
				translation_));
}

sge::collision::point const
sge::ode::transformer::velocity_from_ode(
	point const &_p) const
{
	return 
		math::vector::structure_cast<collision::point>(
			_p*
			static_cast<dReal>(
				inverse_scaling_));
}

sge::collision::dim const
sge::ode::transformer::dim_from_ode(
	dim const &_d) const
{
	return 
		sge::math::dim::structure_cast<collision::dim>(
			static_cast<dReal>(
				inverse_scaling_)*_d);
}

sge::ode::point const sge::ode::transformer::position_to_ode(
	collision::point const &_p) const
{
	return
		math::vector::structure_cast<point>(
			(_p + translation_)*scaling_);
}

sge::ode::point const sge::ode::transformer::velocity_to_ode(
	collision::point const &_p) const
{
	return
		math::vector::structure_cast<point>(
			_p*scaling_);
}

sge::ode::dim const sge::ode::transformer::dim_to_ode(
	collision::dim const &_d) const
{
	return 
		sge::math::dim::structure_cast<dim>(
			_d*scaling_);
}

sge::collision::unit sge::ode::transformer::unit_from_ode(
	dReal const _d) const
{
	return 
		static_cast<collision::unit>(
			_d)*inverse_scaling_;
}

dReal sge::ode::transformer::unit_to_ode(
	collision::unit const _d) const
{
	return 
		static_cast<dReal>(
			_d)*scaling_;
}
