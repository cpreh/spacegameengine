#include "is_solid.hpp"
#include <sge/projectile/body/solidity/nonsolid.hpp>
#include <fcppt/variant/apply_unary.hpp>

namespace
{
class is_solid_visitor
{
public:
	typedef bool result_type;

	result_type
	operator()(
		sge::projectile::body::solidity::nonsolid const &) const
	{
		return false;
	}

	template<typename T>
	result_type
	operator()(
		T const &) const
	{
		return true;
	}
};
}

bool
sge::projectile::body::solidity::is_solid(
	variant const &v)
{
	return 
		fcppt::variant::apply_unary(
			is_solid_visitor(),
			v);
}
