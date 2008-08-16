#include <sge/math/angle.hpp>
#include <sge/math/compare.hpp>
#include <sge/math/constants.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <sge/format.hpp>

sge::space_unit sge::math::rel_angle_to_abs(const space_unit a)
{
	if(!in_closed_interval(a,-pi<space_unit>(),pi<space_unit>()))
		throw exception(
			(format(SGE_TEXT("math::rel_angle_to_abs: relative angle %1% out of range!"))
			% a).str());

	if (almost_zero(a))
		return su(0);

	return a > su(0) ? a : su(2)*pi<space_unit>()+a;
}

sge::space_unit sge::math::abs_angle_to_rel(space_unit a)
{
	a = mod(a,su(2)*pi<space_unit>());

	if (in_closed_interval(a,-pi<space_unit>(),pi<space_unit>()))
		return a;

	return a > pi<space_unit>() 
		? a-su(2)*pi<space_unit>() 
		: a;
}
