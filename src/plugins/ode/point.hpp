#ifndef SGE_ODE_POINT_HPP_INCLUDED
#define SGE_ODE_POINT_HPP_INCLUDED

#include <sge/math/vector/static.hpp>
#include <ode/ode.h>

namespace sge
{
namespace ode
{
typedef math::vector::static_<
	dReal,
	3>::type point;
}
}

#endif
