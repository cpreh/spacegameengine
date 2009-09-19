#ifndef SGE_COLLISION_DIM_HPP_INCLUDED
#define SGE_COLLISION_DIM_HPP_INCLUDED

#include <sge/math/dim/static.hpp>
#include <sge/collision/unit.hpp>

namespace sge
{
namespace collision
{
typedef math::dim::static_<unit,3>::type dim;
}
}

#endif