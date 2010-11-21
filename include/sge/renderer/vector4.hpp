#ifndef SGE_RENDERER_VECTOR4_HPP_INCLUDED
#define SGE_RENDERER_VECTOR4_HPP_INCLUDED

#include <sge/renderer/scalar.hpp>
#include <fcppt/math/vector/static.hpp>

namespace sge
{
namespace renderer
{
typedef
fcppt::math::vector::static_<scalar,4>::type
vector4;
}
}

#endif
