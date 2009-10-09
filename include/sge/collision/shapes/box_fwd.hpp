#ifndef SGE_COLLISION_SHAPES_BOX_FWD_HPP_INCLUDED
#define SGE_COLLISION_SHAPES_BOX_FWD_HPP_INCLUDED

#include <sge/shared_ptr.hpp>

namespace sge
{
namespace collision
{
namespace shapes
{
class box;
typedef shared_ptr<box> box_ptr;
typedef shared_ptr<box const> const_box_ptr;
}
}
}

#endif
