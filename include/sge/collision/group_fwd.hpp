#ifndef SGE_COLLISION_GROUP_FWD_HPP_INCLUDED
#define SGE_COLLISION_GROUP_FWD_HPP_INCLUDED

#include <sge/shared_ptr.hpp>

namespace sge
{
namespace collision
{
class group;
typedef shared_ptr<group> group_ptr;
typedef shared_ptr<group const> const_group_ptr;
}
}

#endif
