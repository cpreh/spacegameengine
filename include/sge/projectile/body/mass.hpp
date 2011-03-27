#ifndef SGE_PROJECTILE_BODY_MASS_HPP_INCLUDED
#define SGE_PROJECTILE_BODY_MASS_HPP_INCLUDED

#include <bullet/LinearMath/btScalar.h>
#include <fcppt/strong_typedef.hpp>

namespace sge
{
namespace projectile
{
namespace body
{
FCPPT_MAKE_STRONG_TYPEDEF(
	btScalar,
	mass);
}
}
}

#endif
