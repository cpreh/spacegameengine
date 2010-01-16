#ifndef SGE_BULLET_BULLET_SHAPE_PTR_HPP_INCLUDED
#define SGE_BULLET_BULLET_SHAPE_PTR_HPP_INCLUDED

#include <fcppt/auto_ptr.hpp>
#include <BulletCollision/CollisionShapes/btCollisionShape.h>

namespace sge
{
namespace bullet
{
typedef 
fcppt::auto_ptr<btCollisionShape> 
bullet_shape_ptr;
}
}

#endif
