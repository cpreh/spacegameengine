#ifndef SGE_PROJECTILE_BODY_COLLISION_HPP_INCLUDED
#define SGE_PROJECTILE_BODY_COLLISION_HPP_INCLUDED

#include <sge/projectile/body/collision_fn.hpp>
#include <fcppt/function/object.hpp>

namespace sge
{
namespace projectile
{
namespace body
{
typedef
fcppt::function::object<collision_fn>
collision;
}
}
}

#endif
