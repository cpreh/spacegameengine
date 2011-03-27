#ifndef SGE_PROJECTILE_GHOST_BODY_ENTER_HPP_INCLUDED
#define SGE_PROJECTILE_GHOST_BODY_ENTER_HPP_INCLUDED

#include <sge/projectile/ghost/body_enter_fn.hpp>
#include <fcppt/function/object.hpp>

namespace sge
{
namespace projectile
{
namespace ghost
{
typedef
fcppt::function::object<body_enter_fn>
body_enter;
}
}
}

#endif
