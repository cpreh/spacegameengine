#ifndef SGE_ODE_BOX_HPP_INCLUDED
#define SGE_ODE_BOX_HPP_INCLUDED

#include <sge/math/box/basic_fwd.hpp>
#include <ode.h>

namespace sge
{
namespace ode
{
typedef math::box::basic
<
	dReal,
	3
> box;
}
}

#endif
