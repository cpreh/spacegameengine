#ifndef SGE_PROJECTILE_TRIANGLE_HPP_INCLUDED
#define SGE_PROJECTILE_TRIANGLE_HPP_INCLUDED

#include <sge/projectile/vector2.hpp>
#include <fcppt/container/array.hpp>
#include <fcppt/math/vector/basic_impl.hpp>

namespace sge
{
namespace projectile
{
typedef
fcppt::container::array
<
	vector2,
	3
>
triangle;
}
}

#endif
