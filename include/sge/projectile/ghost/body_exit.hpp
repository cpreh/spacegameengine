#ifndef SGE_PROJECTILE_GHOST_BODY_EXIT_HPP_INCLUDED
#define SGE_PROJECTILE_GHOST_BODY_EXIT_HPP_INCLUDED

#include <sge/projectile/ghost/body_exit_fn.hpp>
#include <fcppt/function/object.hpp>

namespace sge
{
namespace projectile
{
namespace ghost
{
typedef
fcppt::function::object<body_exit_fn>
body_exit;
}
}
}

#endif
