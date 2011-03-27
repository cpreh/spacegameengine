#ifndef SGE_PROJECTILE_DIM2_HPP_INCLUDED
#define SGE_PROJECTILE_DIM2_HPP_INCLUDED

#include <bullet/LinearMath/btScalar.h>
#include <fcppt/math/dim/static.hpp>

namespace sge
{
namespace projectile
{
typedef
fcppt::math::dim::static_<btScalar,2>::type
dim2;
}
}

#endif
