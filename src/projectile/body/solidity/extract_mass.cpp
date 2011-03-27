#include "extract_mass.hpp"
#include <fcppt/variant/apply_unary.hpp>

namespace
{
struct mass_visitor
{
public:
	typedef
	btScalar
	result_type;

	result_type
	operator()(
		sge::projectile::body::solidity::solid const &s) const
	{
		return s.mass().get();
	}

	result_type
	operator()(
		sge::projectile::body::solidity::static_ const &) const
	{
		return 
			static_cast<btScalar>(
				0);
	}

	result_type
	operator()(
		sge::projectile::body::solidity::nonsolid const &) const
	{
		return 
			static_cast<btScalar>(
				1);
	}
};
}

btScalar
sge::projectile::body::solidity::extract_mass(
	variant const &v)
{
	return 
		fcppt::variant::apply_unary(
			mass_visitor(),
			v);
}
