#ifndef SGE_PROJECTILE_BODY_POSITION_CHANGE_HPP_INCLUDED
#define SGE_PROJECTILE_BODY_POSITION_CHANGE_HPP_INCLUDED

#include <sge/projectile/body/position_change_fn.hpp>
#include <fcppt/function/object.hpp>

namespace sge
{
namespace projectile
{
namespace body
{
typedef
fcppt::function::object<position_change_fn>
position_change;
}
}
}

#endif
