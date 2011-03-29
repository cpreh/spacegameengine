#ifndef SGE_PROJECTILE_BODY_SOLIDITY_EXTRACT_MASS_HPP_INCLUDED
#define SGE_PROJECTILE_BODY_SOLIDITY_EXTRACT_MASS_HPP_INCLUDED

#include <sge/projectile/body/solidity/variant.hpp>
#include <LinearMath/btScalar.h>

namespace sge
{
namespace projectile
{
namespace body
{
namespace solidity
{
btScalar
extract_mass(
	variant const &);
}
}
}
}

#endif
