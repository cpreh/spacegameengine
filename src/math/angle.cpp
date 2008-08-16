#include <sge/math/angle.hpp>
#include <sge/math/compare.hpp>
#include <sge/math/constants.hpp>
#include <sge/math/mod.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <sge/format.hpp>

sge::space_unit sge::math::rel_angle_to_abs(space_unit const a)
{
	if(!is_rel_angle(a))
		throw exception(
			(format(SGE_TEXT("math::rel_angle_to_abs: relative angle %1% out of range!"))
			% a).str());

	if (almost_zero(a))
		return su(0);

	return a > su(0) ? a : twopi<space_unit>()+a;
}

sge::space_unit sge::math::abs_angle_to_rel(space_unit a)
{
	a = mod(a, twopi<space_unit>());

	if (is_rel_angle(a))
		return a;
	
	return a > 0 
		? a - twopi<space_unit>() 
		: a + twopi<space_unit>();
}

bool sge::math::is_rel_angle(space_unit const a)
{
	return in_closed_interval(a, -pi<space_unit>(), pi<space_unit>());
}
