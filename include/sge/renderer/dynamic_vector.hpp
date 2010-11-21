#ifndef SGE_RENDERER_DYNAMIC_VECTOR_HPP_INCLUDED
#define SGE_RENDERER_DYNAMIC_VECTOR_HPP_INCLUDED

#include <sge/renderer/scalar.hpp>
#include <fcppt/math/vector/dynamic.hpp>
#include <fcppt/math/vector/basic_impl.hpp>

namespace sge
{
namespace renderer
{
typedef
fcppt::math::vector::dynamic
<
	scalar
>::type
dynamic_vector;
}
}

#endif
