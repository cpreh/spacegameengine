#ifndef SGE_PROJECTILE_BODY_ROTATION_CHANGE_HPP_INCLUDED
#define SGE_PROJECTILE_BODY_ROTATION_CHANGE_HPP_INCLUDED

#include <sge/projectile/body/rotation_change_fn.hpp>
#include <fcppt/function/object.hpp>

namespace sge
{
namespace projectile
{
namespace body
{
typedef
fcppt::function::object<rotation_change_fn>
rotation_change;
}
}
}

#endif
