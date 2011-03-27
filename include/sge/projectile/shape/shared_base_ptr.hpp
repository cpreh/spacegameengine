#ifndef SGE_PROJECTILE_SHAPE_SHARED_BASE_PTR_HPP_INCLUDED
#define SGE_PROJECTILE_SHAPE_SHARED_BASE_PTR_HPP_INCLUDED

#include <sge/projectile/shape/base_fwd.hpp>
#include <fcppt/shared_ptr.hpp>

namespace sge
{
namespace projectile
{
namespace shape
{
typedef
fcppt::shared_ptr
<
	base
>
shared_base_ptr;
}
}
}

#endif
