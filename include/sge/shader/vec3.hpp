#ifndef SGE_SHADER_VEC3_HPP_INCLUDED
#define SGE_SHADER_VEC3_HPP_INCLUDED

#include <sge/shader/scalar.hpp>
#include <fcppt/math/vector/static.hpp>

namespace sge
{
namespace shader
{
typedef
fcppt::math::vector::static_<scalar,3>::type
vec3;
}
}

#endif
