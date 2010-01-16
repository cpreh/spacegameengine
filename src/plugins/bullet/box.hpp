#ifndef SGE_BULLET_BOX_HPP_INCLUDED
#define SGE_BULLET_BOX_HPP_INCLUDED

#include <fcppt/math/box/basic_fwd.hpp>
#include "unit.hpp"

namespace sge
{
namespace bullet
{
typedef fcppt::math::box::basic
<
	unit,
	3
> box;
}
}

#endif
