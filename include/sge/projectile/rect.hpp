#ifndef SGE_PROJECTILE_RECT_HPP_INCLUDED
#define SGE_PROJECTILE_RECT_HPP_INCLUDED

#include <bullet/LinearMath/btScalar.h>
#include <fcppt/math/box/rect.hpp>

namespace sge
{
namespace projectile
{
typedef
fcppt::math::box::rect<btScalar>::type
rect;
}
}

#endif
