#ifndef SGE_PROJECTILE_GROUP_ID_HPP_INCLUDED
#define SGE_PROJECTILE_GROUP_ID_HPP_INCLUDED

#include <bullet/BulletCollision/BroadphaseCollision/btBroadphaseProxy.h>
#include <boost/typeof/typeof.hpp>

namespace sge
{
namespace projectile
{
namespace group
{
// MWHAHAHAHA YEAAAAAAAAAAHHHHHH
typedef
BOOST_TYPEOF(btBroadphaseProxy().m_collisionFilterGroup)
id;
}
}
}

#endif
