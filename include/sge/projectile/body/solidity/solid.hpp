#ifndef SGE_PROJECTILE_BODY_SOLIDITY_SOLID_HPP_INCLUDED
#define SGE_PROJECTILE_BODY_SOLIDITY_SOLID_HPP_INCLUDED

#include <sge/projectile/body/mass.hpp>
#include <sge/projectile/symbol.hpp>

namespace sge
{
namespace projectile
{
namespace body
{
namespace solidity
{
class solid
{
public:
	SGE_PROJECTILE_SYMBOL explicit
	solid(
		sge::projectile::body::mass const &);

	SGE_PROJECTILE_SYMBOL sge::projectile::body::mass const &
	mass() const;
private:
	sge::projectile::body::mass mass_;
};
}
}
}
}

#endif
