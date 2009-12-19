#ifndef SGE_ODE_POINT_HPP_INCLUDED
#define SGE_ODE_POINT_HPP_INCLUDED

#include <fcppt/math/vector/static.hpp>
#include <ode/ode.h>

namespace sge
{
namespace ode
{
typedef sge::math::vector::static_<dReal,3>::type point;
}
}

#endif