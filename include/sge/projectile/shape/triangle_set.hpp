#ifndef SGE_PROJECTILE_SHAPE_TRIANGLE_SET_HPP_INCLUDED
#define SGE_PROJECTILE_SHAPE_TRIANGLE_SET_HPP_INCLUDED

#include <sge/projectile/triangle.hpp>
#include <sge/projectile/detail/triangle_set_hash.hpp>
#include <fcppt/tr1/unordered_set.hpp>

namespace sge
{
namespace projectile
{
namespace shape
{
typedef
std::tr1::unordered_set
<
	triangle,
	detail::triangle_set_hash
>
triangle_set;
}
}
}

#endif
