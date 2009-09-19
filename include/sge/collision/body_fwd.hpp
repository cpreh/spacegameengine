#ifndef SGE_COLLISION_BODY_FWD_HPP_INCLUDED
#define SGE_COLLISION_BODY_FWD_HPP_INCLUDED

#include <sge/shared_ptr.hpp>

namespace sge
{
namespace collision
{
class body;
typedef shared_ptr<body> body_ptr;
typedef shared_ptr<body const> const_body_ptr;
}
}

#endif
