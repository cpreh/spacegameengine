#ifndef SGE_PROJECTILE_BODY_COLLISION_FN_HPP_INCLUDED
#define SGE_PROJECTILE_BODY_COLLISION_FN_HPP_INCLUDED

#include <sge/projectile/body/object_fwd.hpp>

namespace sge
{
namespace projectile
{
namespace body
{
typedef
void
collision_fn(
	object const &,
	object const &);
}
}
}

#endif
